.. raw:: html

    <details>
    <summary>Full source code Gtfw Cpu</summary>

.. code-block:: php
   :linenos: 
   :caption: Source code @main/system/core/cpu/GtfwCpu.class.php

    <?php
    /*
        - self:: akses property / fungsi yang ada di class ini.
        - konstanta GTFW_BASE_DIR_CORE, BACKWARD_COMPATIBLE, GTFW_APP_DIR ada di index
    */
    class GtfwCpu {
        public static $system;
        public static $module = array();
        private static $setting = array();
        private static $message = array();
        
        /*
            - new stdClass() membuat objek kosong.
            - ini_get('magic_quotes_gpc') mengembalikan nilai konfigurasi magic_quotes_gpc yang ada di file php.ini jika ada.
        */
        public static function Initialize(){
            self::$system = new stdClass();
            self::$setting['magic_quotes'] = ini_get('magic_quotes_gpc');

            include GTFW_BASE_DIR_CORE . 'base/GtfwBase.class.php';
            include GTFW_BASE_DIR_CORE . 'cpu/GtfwCpu.helper.php';
            include GTFW_BASE_DIR_CORE . 'sharedpreference/GtfwSharedPreference.class.php';
            include GTFW_BASE_DIR_CORE . 'database/GtfwDatabase.class.php';
            
            self::initConfiguration();
            self::initSanitizer();
            
            //============= DISPATCHER =============
            include GTFW_BASE_DIR_CORE . 'dispatcher/GtfwDispatcher.class.php';
            //============= end of DISPATCHER =============
            
            self::initSession();
            self::initEncryption();
            self::initSecurity();
            
            //============= MESSENGER =============
            include GTFW_BASE_DIR_CORE . 'messenger/GtfwMessenger.class.php';
            self::$system->GtfwMessenger = GtfwMessenger::Initialize();
            //============= end of MESSENGER =============
            
            
            // BACKWARD AREA
            if(BACKWARD_COMPATIBLE){
                include GTFW_BASE_DIR_CORE . 'configuration/Configuration.class.php';
                Configuration::Initialize();
                class_alias('GtfwSession', 'Session');
                class_alias('GtfwSecurity', 'Security');
                
                include GTFW_BASE_DIR_CORE . 'sanitizer/GtfwSanitizerFactory.class.php';
                include GTFW_BASE_DIR_CORE . 'dispatcher/Dispatcher.class.php';
                
                $raw = $_GET;
                $_GET = GtfwSanitizerFactory::Wrap($_GET);
                $_GET['raw_request'] = $raw;
                $raw = $_POST;
                $_POST = GtfwSanitizerFactory::Wrap($_POST);
                $_POST['raw_request'] = $raw;
                $_COOKIE = GtfwSanitizerFactory::Wrap($_COOKIE);
                $raw = $_GET;
                $_REQUEST = GtfwSanitizerFactory::Wrap($_REQUEST);
                $_REQUEST['raw_request'] = $raw;
                
                include GTFW_BASE_DIR_CORE . 'router/Router.class.php';
                self::$system->GtfwRouter = Router::Initialize();
                self::$system->GtfwDispatcher = Dispatcher::Initialize();
            }else{
                self::initSystemModule();
                include GTFW_BASE_DIR_CORE . 'sanitizer/GtfwSanitizer.helper.php';
                $raw = $_GET;
                $_GET = sanitize($_GET);
                $_GET['raw_request'] = $raw;
                $raw = $_POST;
                $_POST = sanitize($_POST);
                $_POST['raw_request'] = $raw;
                $raw = $_GET;
                $_REQUEST = sanitize($_REQUEST);
                $_REQUEST['raw_request'] = $raw;
                
                include GTFW_BASE_DIR_CORE . 'router/GtfwRouter.class.php';
                include GTFW_BASE_DIR_CORE . 'base/GtfwBaseModule.class.php';
                self::$system->GtfwRouter = GtfwRouter::Initialize();
                self::$system->GtfwDispatcher = GtfwDispatcher::Initialize();
            }
        }
        
        public static function process(){
            header('Cache-Control: no-cache, must-revalidate');
            header('Expires: Mon, 26 Jul 1997 05:00:00 GMT');
            
            // selalu load gtfw_module object untuk support pustaka
            if(GTFW_BASE_GTPUSTAKA or (self::$system->GtfwConfiguration->get('application', 'url_type') == 'Short')){
                include GTFW_BASE_DIR_BUSINESS . 'GtfwModule/GtfwModuleBase.class.php';
                self::$module['GtfwModuleBase'] = new GtfwModuleBase();
            }
            
            self::$message['activeModule'] = $request = self::$system->GtfwDispatcher->Dispatch();
            SharedPreference::Instance()->setProp('activeModule', $request);
            if(DEVELOPMENT){
                setLog("\nModule Requested : " . var_export($request,true), 'System');
            }

            if(!isset(self::$message['systemModule'][$request['module']])){
                $mode = (bool)self::$system->GtfwConfiguration->get('application', 'enable_security');
                if($mode){
                    if(!self::$system->GtfwSecurity->AllowedToAccess($request['module'], $request['submodule'], $request['action'], $request['type'])){
                        self::$system->GtfwSecurity->ModuleAccessDenied();
                        if(DEVELOPMENT){
                            $sysMsg = getLog('System');
                            $dbMsg = getLog('Database');
                            $phpMsg = getLog('PHP');
                            echo "<pre>";
                            print_r($sysMsg);
                            echo "</pre>";
                            echo "<hr />";
                            echo "<pre>";
                            print_r($dbMsg);
                            echo "</pre>";
                            echo "<hr />";
                            echo "<pre>";
                            print_r($phpMsg);
                            echo "</pre>";
                        }
                        die;
                    }
                }
                self::$message['gtfw_default'] = false;
            }else self::$message['gtfw_default'] = true;

            // auto load additional object
            spl_autoload_register(function($className){
                $dir = strtolower($className);
                $file = GTFW_BASE_DIR_CORE . $dir . '/Gtfw' . $className . '.class.php';
                if(file_exists($file))include $file;
                else{
                    $target = GTFW_BASE_DIR_LIBRARIES . $dir;
                    if(file_exists($target)){
                        $fileName = $dir . '.class.php';
                        if($handle = opendir($target)){
                            while(false !== ($file = readdir($handle))){
                                if($file{0} !== '.'){
                                    if(strtolower($file) === $fileName){
                                        include $target . '/' . $file;
                                        break;
                                    }
                                }
                            }
                            closedir($handle);
                        }
                    }else{
                        $file = GTFW_APP_DIR_EXTENDS . $dir . '/' . $className . '.class.php';
                        if(file_exists($file))include $file;
                    }
                }
            });

            if(BACKWARD_COMPATIBLE){
                // include response type (gtfw 3 style), deprecated soon on gtfw 4
                include GTFW_BASE_DIR_RESPONSE . $request['type'] . '/' . ucfirst($request['type']) . 'Response.class.php';
                self::$system->GtfwRouter->handle($request);
            }else{
                include GTFW_BASE_DIR_CORE . 'response/GtfwResponse.class.php';
                include GTFW_BASE_DIR_CORE . 'output/GtfwOutput.class.php';
                $data = self::$system->GtfwRouter->handle($request);
                
                $gtfwOutput = GtfwOutput::Initialize();
                $gtfwOutput->setOperation($request['type']);
                $gtfwOutput->format($data);
            }
            
        }
        
        public static function getTempDir(){
            return self::$setting['tmpDir'];
        }
        
        public static function Encrypt($string){
            $func = self::$setting['enc'];
            return self::$func($string);
        }
        
        public static function Decrypt($string){
            $func = self::$setting['dec'];
            return self::$func($string);
        }
        
        public static function getMessage($msg){
            if(isset(self::$message[$msg]))return self::$message[$msg];
        }
        
        public static function getJsVersion(){
            $result = 0;
            $path = GTFW_BASE_DIR . 'main/system/js';
            $d = explode("\n",@file_get_contents($path.'list.inc'));
            for($i=0,$m=count($d);$i<$m;++$i){
                $filepath = $path.$d[$i];
                if(is_file($filepath) && filectime($filepath) > $result)$result = filectime($filepath);
            }
            return time();
        }
        
        // private area
        private static function enc($string){
            return self::$system->GtfwEncryption->enc((string)$string);
        }
        
        private static function dec($string){
            return self::$system->GtfwEncryption->dec((string)$string);
        }
        
        private static function noenc($string){return (string)$string;}
        
        private static function nodec($string){return (string)$string;}
        
        /* 
            include file GtfwConfiguration.class.php
            
        */
        private static function initConfiguration(){
            include GTFW_BASE_DIR_CORE . 'configuration/GtfwConfiguration.class.php';
            $gtfwConfig = GtfwConfiguration::Initialize();
            $dir = GTFW_APP_DIR . 'config/';
            $gtfwConfig->configDir($dir);
            $gtfwConfig->LoadConfig();
            
            // get temp dir
            $dir = $gtfwConfig->get('system', 'tmp_dir');
            if(!isset($dir) or empty($dir) or !file_exists($dir)){
                $dir = ini_get('upload_tmp_dir');
                if(empty($dir) or !file_exists($dir)){
                    $dir = sys_get_temp_dir();
                }
                if($dir[strlen($dir)-1]!='/')$dir .= '/';
                $gtfwConfig->set('system', 'tmp_dir', $dir);
            }
            self::$setting['tmpDir'] = $dir;
            
            
            $timezone = ini_get('date.timezone');
            if(empty($timezone)){
                $timezone = $gtfwConfig->get('application','timezone');
                if(empty($timezone))$timezone='Asia/Jakarta';
                ini_set('date.timezone',$timezone);
            }
            
            // check available index in $_SERVER
            if(isset($_SERVER['REQUEST_SCHEME']))
                $request_scheme = $_SERVER['REQUEST_SCHEME']; 
            else{
                $request_scheme = 'http';
                if(isset($_SERVER['HTTPS']) && $_SERVER['HTTPS'] == 'on'){
                    $request_scheme = 'https';
                }elseif((isset($_SERVER['HTTP_X_FORWARDED_PROTO']) && $_SERVER['HTTP_X_FORWARDED_PROTO'] == 'https') || (isset($_SERVER['HTTP_X_FORWARDED_SSL']) && $_SERVER['HTTP_X_FORWARDED_SSL'] == 'on')){
                    $request_scheme = 'https';
                }
            }

            // overwrite baseaddress dynamic by browser request
            $gtfwConfig->set('application', 'baseaddress',  $request_scheme. '://' . ((isset($_SERVER['SERVER_NAME']) and !empty($_SERVER['SERVER_NAME']))?$_SERVER['SERVER_NAME']:$_SERVER['HTTP_HOST']) . (($_SERVER['SERVER_PORT'] != 80)?':' . $_SERVER['SERVER_PORT']:''));

            // overwrite basedir dynamic by browser request
            $base = str_replace('\\', '/', dirname($_SERVER['SCRIPT_NAME']));
            $tmp = explode('/', $base);
            for($i = 0, $m = count($tmp); $i < $m; ++$i)$tmp[$i] = rawurlencode($tmp[$i]);
                $base = implode('/', $tmp);
            if($base{strlen($base)-1} !== '/')$base .= '/';
            $gtfwConfig->set('application', 'basedir', $base);

            self::$system->GtfwConfiguration = $gtfwConfig;
            $isPustaka = $gtfwConfig->get('application','forbidden_module');
            if(isset($isPustaka))define('GTFW_BASE_GTPUSTAKA', true);
            else define('GTFW_BASE_GTPUSTAKA', false);
        }

        private static function initSession(){
            include GTFW_BASE_DIR_CORE . 'session/GtfwSession.class.php';
            self::$system->GtfwSession = GtfwSession::Initialize();
            self::$system->GtfwSession->Start();
        }

        private static function initSanitizer(){
            include GTFW_BASE_DIR_CORE . 'sanitizer/GtfwSanitizer.class.php';
            self::$system->GtfwSanitizer = GtfwSanitizer::Initialize(self::$setting['magic_quotes']);
        }

        private static function initEncryption(){
            if((bool)self::$system->GtfwConfiguration->get('application', 'enable_url_obfuscator')){
                if(!isset($_SESSION['gtfw_key'])){
                    $_SESSION['gtfw_key'] = mt_rand(1024, mt_getrandmax());
                }
                include GTFW_BASE_DIR_CORE . 'encryption/GtfwEncryption.class.php';
                $gtfwEncryption = GtfwEncryption::Initialize();
                $gtfwEncryption->setKey($_SESSION['gtfw_key']);
                self::$system->GtfwEncryption = $gtfwEncryption;
                self::$setting['enc'] = 'enc';
                self::$setting['dec'] = 'dec';
            }else{
                self::$setting['enc'] = 'noenc';
                self::$setting['dec'] = 'nodec';
            }
        }

        private static function initSecurity(){
            include GTFW_BASE_DIR_CORE . 'security/GtfwSecurityBase.class.php';
            if((bool)self::$system->GtfwConfiguration->get('application', 'enable_security')){
                include GTFW_BASE_DIR_CORE . 'security/GtfwSecurity.class.php';
                self::$system->GtfwSecurity = GtfwSecurity::Initialize();
            }else{
                self::$system->GtfwSecurity = GtfwSecurityBase::Initialize();
                class_alias('GtfwSecurityBase', 'GtfwSecurity');
            }
        }

        private static function initSystemModule(){
            include GTFW_BASE_DIR_CORE . 'cpu/GtfwModule.res.php';
            self::$message['systemModule'] = $resModule;
            self::$message['systemModuleDefault'] = array(
                'module'	=> 'gtfw_login',
                'submodule'	=> 'login',
                'action'	=> 'view',
                'type'		=> 'html'
            );
        }
    }
    ?>

.. raw:: html

    </details>
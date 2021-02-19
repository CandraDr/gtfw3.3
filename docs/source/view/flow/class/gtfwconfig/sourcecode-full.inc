.. raw:: html

    <details>
    <summary>Full source code GtfwConfiguration</summary>

.. code-block:: php
   :linenos: 
   :caption: Source code @main/system/core/GtfwConfiguration.class.php

    <?php
    /**
    GtfwConfiguration
        class untuk menangani config aplikasi

    @author 	:	Wahyu A.Y

    @modified	:
    @copyright 2014 Gamatechno
    */

    class GtfwConfiguration extends GtfwBaseSingleton{
        private $mHandlers = array();
        private $mCache = array();
        private $cacheFile = '';
        private $cacheTimestamp = 0;
        private $cacheFileExists = false;
        private $mDir = '';
        private $mWrite = false;
        private $mConfigFilenameBase = array('conf.php'	=> true, 'conf.ini'	=> true);
        
        public function Load($configFilename, $handler = 'default'){
            $name = explode('.', $configFilename, 2);
            if(isset($this->mConfigFilenameBase[$name[1]])){
                $name = strtolower($name[0]);
                $configFilename = $this->mDir . $configFilename;
                
                if($this->cacheFileExists and !($this->cacheTimestamp < filemtime($configFilename)))$read = false;
                else $read = true;
                
                if($read){
                    $this->mWrite = true;
                    if(!isset($this->mHandlers[$handler])){
                        $handler_class = ucwords(str_replace('_', ' ', $handler));
                        $handler_class = str_replace(' ', '', $handler_class) . 'ConfigHandler';
                        $file = GTFW_BASE_DIR_CORE . '/configuration/configuration_handler/' . $handler . '/' . $handler_class . '.class.php';
                        if(!file_exists($file))die('Can not find ' . $handler . ' Configuration Handler');
                        include $file;
                        $this->mHandlers[$handler] = new $handler_class();
                    }

                    // === backward, deprecated soon
                    if($handler === 'default')$name = 'application';
                    // ===
                    
                    $res = $this->mHandlers[$handler]->Load($configFilename);
                    $this->_setArray($name, $res);
                }
            }
        }
        
        public function LoadConfig(){
            if($handle = opendir($this->mDir)){
                $handler = array(
                    'ini'	=> 'ini',
                    'php'	=> 'default'
                );
                while(false !== ($file = readdir($handle))){
                    if($file{0} !== '.'){
                        $ext = explode('.', $file);
                        $ext = $ext[count($ext)-1];
                        if(isset($handler[$ext]))$this->Load($file, $handler[$ext]);
                    }
                }

                closedir($handle);
            }
        }
        
        public function get($args){
            if(!is_array($args))$args = func_get_args();
            if(isset($args[0])){
                $args[0] = strtolower($args[0]);
                $name = $args[0];
                if(isset($args[1]) and is_array($args[1])){
                    // format param = name, array(.., .., ...)
                    $args = $args[1];
                    $key = $name . '::' . implode('::', $args);
                }else{
                    // format param = .., .., ...
                    $key = implode('::', $args);
                }
                return isset($this->mCache[$key])?$this->mCache[$key]:null;
            }
        }

        public function set($config_name, $key, $value){
            $key = $config_name . '::' . $key;
            $this->mCache[$key] = $value;
            return true;
        }

        public function configDir($dir){
            $this->mDir = $dir;

            /*this made unstable*/
            // if(!DEVELOPMENT){
            // 	$this->cacheFile = $this->mCache['system::cache_dir'] . md5($dir);
            // 	if(file_exists($this->cacheFile)){
            // 		$this->cacheFileExists = true;
            // 		$tmp = $this->mCache['system::cache_dir'];
            // 		$this->mCache = json_decode(file_get_contents($this->cacheFile), true);
            // 		$this->mCache['system::cache_dir'] = $tmp;
            // 		$this->cacheTimestamp = filemtime($this->cacheFile);
            // 	}
            // }
        }
        
        public function destroy(){
            if($this->mWrite and !DEVELOPMENT and file_exists($this->cacheFile))file_put_contents($this->cacheFile, json_encode($this->mCache));
        }
        
        protected function init(){
            $tmp = sys_get_temp_dir() . '/';
            $this->mCache['system::cache_dir'] = $tmp;
        }
        
        // backward compatibility, deleted soon
        public static function GetValue(){
            return self::Instance()->get(func_get_args());
        }
        
        public static function SetValue($config_name, $key, $value){
            return self::Instance()->set($config_name, $key, $value);
        }

        public static function IsExist($config_name, $key) {
            $val = self::Instance()->get($config_name, $key);
            return isset($val)?true:false;
        }

        public static function SetConfigDirectory($value){}
        
        public function getVersion(){return $this->gtfwVersion;}

        public function GetTempDir(){
            return $this->get('system', 'temp_dir');
        }

        protected function _setArray($name, $arr){
            foreach($arr as $k => $v){
                $this->set($name, $k, $v);
                if(is_array($v)){
                    $this->_setArray($name . '::' . $k, $v);
                }
            }
        }
        
    }
    ?>

.. raw:: html

    </details>
.. _gtfwcpu-initconfig:

initConfiguration()
===================

* Set path menuju folder config Gtfw App.
* Load file-file configuration dengan fungsi :ref:`loadConfig() <gtfwconfig-loadconfig>`.
* Get path menuju temporary directory. Lakukan set temp dir jika konfigurasi tidak ditemukan. Cth: C:/xampp/tmp/
* Get zona waktu. Lakukan set zona waktu Asia/Jakarta ke file php.ini jika konfigurasi tidak ditemukan.
* Cek skema request server apakah http atau https.
* Set baseaddress dan basedir. Cth: http://localhost:8080/ & /latihan/newrms/dokumentasi-gtfw/gtfw-3.3-base

.. raw:: html

    <details>
    <summary>Source code fungsi initConfiguration()</summary>

.. code-block:: php
   :linenos: 
   :caption: Source code @main/system/core/cpu/GtfwCpu.class.php

    <?php
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
    ?>

.. raw:: html

    </details>

Referensi ke file lain:

#. :ref:`GtfwConfiguration <gtfwconfig>` - line 6, 7, 10, 17, 23, 41, 49, 52.
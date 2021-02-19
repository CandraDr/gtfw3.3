.. _gtfwcpu-initialize:

Initialize()
============

* Inisialisasi proses-proses awal yang diperlukan.
* Terdapat perbedaan pada proses sanitzer, router dan dispatcher, jika dukungan untuk gtfw lama diperbolehkan.

.. raw:: html

    <details>
    <summary>Source code fungsi Initialize()</summary>

.. code-block:: php
   :linenos: 
   :caption: Source code @main/system/core/cpu/GtfwCpu.class.php

    <?php
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
    ?>

.. raw:: html

    </details>

Referensi ke file lain:

#. :ref:`GtfwMessenger <gtfwmessenger>` - line 24.
#. Jika dukungan untuk gtfw lama diperbolehkan:
    #. :ref:`Configuration <config>` - line 31.
    #. :ref:`GtfwSanitizerFactory <gtfwsanitizerfactory>` - line 39, 42, 44, 46
    #. Router - line 50.
    #. Dispatcher - line 51.
#. Jika tidak:
    #. :ref:`GtfwSanitizer <gtfwsanitizer>` - line 56, 59, 62.
    #. GtfwRouter - line 67.
    #. GtfwDispatcher - line 68.
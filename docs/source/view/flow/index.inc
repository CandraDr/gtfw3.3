.. _flow-index:

*****
Index
*****

* File pertama yang diakses. 
* Mengecek apakah versi php yang terinstall sudah versi 5.3/lebih.
* Melakukan pengecekan apakah konstanta sudah didefinisi, jika belum definisikan.
* Menampilkan semua error dalam mode development, jika tidak hanya menampilkan error yang sedang berjalan.
* Memulai proses benchmark dan Gtfw Cpu.

.. raw:: html

    <details>
    <summary>Full source code Index</summary>

.. code-block:: php
   :linenos:
   :caption: Source code @index.php

    <?php
    // PRE ALPHA
    if(!function_exists('get_called_class'))die('This application require PHP 5.3 or above');

    if(!defined('GTFW_BASE_DIR'))define('GTFW_BASE_DIR', realpath(dirname(__file__)) . '/');
    if(!defined('GTFW_APP_DIR'))define('GTFW_APP_DIR', getcwd() . '/');
    if(!defined('BACKWARD_COMPATIBLE'))define('BACKWARD_COMPATIBLE', true);
    if(!defined('DEVELOPMENT'))define('DEVELOPMENT', false);
    if(!defined('DEVELOPMENT_BASE'))define('DEVELOPMENT_BASE', false);

    if(DEVELOPMENT){
        error_reporting(E_ALL);
    }else{
        error_reporting(E_ERROR);
    }
    // ini_set('display_errors',0);

    // matikan profiler by default
    if (!defined('GTFW_ENABLE_PROFILER')) define('GTFW_ENABLE_PROFILER', false);

    if (!defined('GTFW_BASE_DIR_CORE')) define('GTFW_BASE_DIR_CORE', GTFW_BASE_DIR . 'main/system/core/');
    if (!defined('GTFW_BASE_DIR_RESPONSE')) define('GTFW_BASE_DIR_RESPONSE', GTFW_BASE_DIR . 'main/system/response/');
    if (!defined('GTFW_BASE_DIR_LIBRARIES')) define('GTFW_BASE_DIR_LIBRARIES', GTFW_BASE_DIR . 'main/system/libraries/');
    if (!defined('GTFW_BASE_DIR_BUSINESS')) define('GTFW_BASE_DIR_BUSINESS', GTFW_BASE_DIR . 'main/system/business/');
    if (!defined('GTFW_BASE_DIR_MODULE')) define('GTFW_BASE_DIR_MODULE', GTFW_BASE_DIR . 'main/system/module/');
    if (!defined('GTFW_APP_DIR_EXTENDS')) define('GTFW_APP_DIR_EXTENDS', GTFW_APP_DIR . 'extends/');

    //version code
    if (!defined('GTFW_CODE_NUMBER')) define('GTFW_CODE_NUMBER', 2);

    include GTFW_BASE_DIR_LIBRARIES . 'simple_benchmark/SimpleBenchmark.class.php';
    SimpleBenchmark::Initialize();
    SimpleBenchmark::Instance()->start();

    include GTFW_BASE_DIR_CORE . 'cpu/GtfwCpu.class.php';
    GtfwCpu::Initialize();
    GtfwCpu::process();
    ?>

.. raw:: html

    </details>

Referensi ke class lain:

#. :ref:`SimpleBenchmark <benchmark>` - line 32, 33.
#. :ref:`GtfwCpu <gtfwcpu>` - line 36, 37.
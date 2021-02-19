.. _gtfwcpu-initsanitizer:

initSanitizer()
===============

* Inisialisasi class GtfwSession kedalam property system->GtfwSession.
* Mulai proses session.

.. code-block:: php
   :linenos: 
   :caption: Source code @main/system/core/cpu/GtfwCpu.class.php

    <?php
    private static function initSession(){
        include GTFW_BASE_DIR_CORE . 'session/GtfwSession.class.php';
        self::$system->GtfwSession = GtfwSession::Initialize();
        self::$system->GtfwSession->Start();
    }
    ?>
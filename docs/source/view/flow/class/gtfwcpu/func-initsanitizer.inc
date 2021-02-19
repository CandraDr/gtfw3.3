.. _gtfwcpu-initsanitizer:

initSanitizer()
===============

Inisialisasi class GtfwSanitizer kedalam property system->GtfwSanitizer.

.. code-block:: php
   :linenos: 
   :caption: Source code @main/system/core/cpu/GtfwCpu.class.php

    <?php
    private static function initSanitizer(){
        include GTFW_BASE_DIR_CORE . 'sanitizer/GtfwSanitizer.class.php';
        self::$system->GtfwSanitizer = GtfwSanitizer::Initialize(self::$setting['magic_quotes']);
    }
    ?>
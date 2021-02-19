.. _gtfwsanitizerfactory-wrap:

Wrap()
======

Membungkus isi array dari parameter compound yang sudah di sanitize kedalam object GtfwSanitizerFactory.

.. code-block:: php
   :linenos: 
   :caption: Source code @main/system/core/sanitizer/GtfwSanitizerFactory.class.php

    <?php
    public static function Wrap($compound, $skipSanitize = false) {
        $vb = new GtfwSanitizerFactory();
        $vb->DoInit($compound, $skipSanitize);
        unset($compound);

        return $vb;
    }
    ?>
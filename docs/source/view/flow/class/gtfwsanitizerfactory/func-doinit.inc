.. _gtfwsanitizerfactory-doinit:

DoInit()
========

Inisialisasi proses sanitize.

.. code-block:: php
   :linenos: 
   :caption: Source code @main/system/core/sanitizer/GtfwSanitizerFactory.class.php

    <?php
    // ubah jadi langsung sanitize saat init
    protected function DoInit($var, $skipSanitize = false){
        if(!$this->mInitialized){
            $this->mInitialized = true;
            // $this->mRaw = $var;
            if(!$skipSanitize) $this->mCompound = $this->Sanitize($var);
            else{
                // $var = GtfwCpu::$system->GtfwSanitizer->SqlString($var);
                // if(GtfwCpu::$system->GtfwConfiguration->get('application', 'strip_html_tags')) {
                // 	$var = GtfwCpu::$system->GtfwSanitizer->stripTags($var);
                // }
                $var = GtfwCpu::$system->GtfwSanitizer->PregReplace($var);
                $this->mCompound = $var;
            }
            $this->mRaw = $this->mCompound;
        }
    }
    ?>

Referensi ke file lain:

#. :ref:`GtfwSanitizer <gtfwsanitizer>` - line 13
.. _gtfwsanitizerfactory-sanitize:

Sanitize()
==========

* Jika parameter adalah sebuah array, maka jalankan kembali fungsi ini dengan parameter dari value array.
* Jika tidak, maka sanitaze input menggunakan fungsi :ref:`PregReplace() <gtfwsanitizer-pregreplace>` dan bungkus kedalam objek GtfwSanitizerFactory.

.. code-block:: php
   :linenos: 
   :caption: Source code @main/system/core/sanitizer/GtfwSanitizerFactory.class.php

    <?php
    private function Sanitize($compound){
        if(is_array($compound)){
            $result = array();

            foreach($compound as $key => $value){
                $result[$key] = $this->Sanitize($value);
            }
        }else{
            $compound = GtfwCpu::$system->GtfwSanitizer->PregReplace($compound);
            $result = GtfwSanitizerFactory::Wrap($compound, true);
        }

        return $result;
    }
    ?>

Referensi ke file lain:

#. :ref:`GtfwSanitizer <gtfwsanitizer>` - line 10
.. _gtfwconfig-configdir:

ConfigDir()
===========

Assign parameter yang berisi path ke folder config di Gtfw App kedalam property mDir.

.. code-block:: php
   :linenos: 
   :caption: Source code @main/system/core/GtfwConfiguration.class.php

    <?php
    public function configDir($dir){
        $this->mDir = $dir;
    }
    ?>

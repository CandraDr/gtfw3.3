.. _gtfwconfig-set:

set()
=====

* Simpan konfigurasi baru.
* Gabungkan parameter config_name dan key menjadi satu string untuk digunakan sebagai key dari array.
* Simpan key dan value di property mCache.


.. code-block:: php
   :linenos: 
   :caption: Source code @main/system/core/GtfwConfiguration.class.php

	<?php
	public function set($config_name, $key, $value){
        $key = $config_name . '::' . $key;
        $this->mCache[$key] = $value;
        return true;
	}
	?>
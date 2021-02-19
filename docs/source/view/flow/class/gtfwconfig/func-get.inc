.. _gtfwconfig-get:

get()
=====

* Jika parameter bukan sebuat array, maka buat array daftar argumen dari parameter args.
* Jika bukan, gabungkan daftar argumen didalam array menjadi satu string. Cth: array(system, tmp_dir) menjadi system::tmp_dir.
* Mengambil nilai konfigurasi yang dicari menggunakan key dari poin diatas. Cth: system::tmp_dir mendapatkan path menuju temporary directory C:/xampp/tmp/.
* Sebelumnya konfigurasi sudah diset terlebih dahulu dengan fungsi :ref:`set() <gtfwconfig-set>`.

.. code-block:: php
   :linenos: 
   :caption: Source code @main/system/core/GtfwConfiguration.class.php

	<?php
	public function get($args){
		if(!is_array($args))$args = func_get_args();
		if(isset($args[0])){
			$args[0] = strtolower($args[0]);
			$name = $args[0];
			if(isset($args[1]) and is_array($args[1])){
				// format param = name, array(.., .., ...)
				$args = $args[1];
				$key = $name . '::' . implode('::', $args);
			}else{
				// format param = .., .., ...
				$key = implode('::', $args);
			}
			return isset($this->mCache[$key])?$this->mCache[$key]:null;
		}
	}
	?>
.. _gtfwsession-init:

init()
======

* Fungsi yang pertama kali dijalankan ketika class GtfwSession di inisialisasi.
* Set property yang ada dari konfigurasi di class GtfwConfiguration.
* Set session save path dan session expire.

.. raw:: html

    <details>
    <summary>Source code fungsi init()</summary>

.. code-block:: php
   :linenos: 
   :caption: Source code @main/system/core/session/GtfwSession.class.php

    <?php
	protected function init(){
		$this->mSessionIsStarted = false;
		$this->mName = GtfwCpu::$system->GtfwConfiguration->get('application', 'session_name');
		$this->mSavePath = GtfwCpu::$system->GtfwConfiguration->get('application', 'session_save_path');
		$this->mExpire = GtfwCpu::$system->GtfwConfiguration->get('application', 'session_expire');
		$this->mCookieParam = GtfwCpu::$system->GtfwConfiguration->get('application', 'session_cookie_params');
		$this->mSaveHandler = GtfwCpu::$system->GtfwConfiguration->get('application', 'session_save_handler');
		$this->mSessionDir = GtfwCpu::$system->GtfwConfiguration->get('application', 'sessiondir');
		$this->mBaseDir = GtfwCpu::$system->GtfwConfiguration->get('application', 'basedir');
		
		// set session save path
		if(!is_dir($this->mSavePath)){
			$this->mSavePath = ini_get('session.save_path');
			if(!is_dir($this->mSavePath))$this->mSavePath = GtfwCpu::getTempDir();
			else $this->mSavePath = realpath($this->mSavePath) . '/';
		}
		session_save_path($this->mSavePath);

		// set session expire
		if(isset($this->mExpire))session_cache_expire($this->mExpire);
		else $this->mExpire = session_cache_expire();
		$this->mExpire = $this->mExpire * 60;
		
		if(isset($this->mName))session_name($this->mName);
		else $this->mName = session_name();
		
		if(!isset($this->mSaveHandler))$this->mSaveHandler = 'default';
		
		$this->PrepareSaveHandler();
	}
    ?>
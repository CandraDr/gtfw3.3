.. _gtfwconfig-loadconfig:

LoadConfig()
============

Load file configuration berekstensi .ini dan .php dengan path yang sudah diassign dari fungsi :ref:`ConfigDir() <gtfwconfig-configdir>`.

.. code-block:: php
   :linenos: 
   :caption: Source code @main/system/core/GtfwConfiguration.class.php

    <?php
    public function LoadConfig(){
        if($handle = opendir($this->mDir)){
            $handler = array(
                'ini'	=> 'ini',
                'php'	=> 'default'
            );

            while(false !== ($file = readdir($handle))){
                if($file{0} !== '.'){
                    $ext = explode('.', $file);
                    $ext = $ext[count($ext)-1];
                    if(isset($handler[$ext]))$this->Load($file, $handler[$ext]);
                    // echo $file."<br>";
                }
            }
            
            closedir($handle);
        }
    }
    ?>
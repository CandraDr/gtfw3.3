.. _gtfwsession_preparesavehandler:

PrepareSaveHandler()
====================

.. code-block:: php
   :linenos: 
   :caption: Source code @main/system/core/session/GtfwSession.class.php

    <?php
    // prepare save handler object
    public function PrepareSaveHandler(){
        if($this->mSaveHandler != 'default'){
            $save_handler_class = str_replace(' ', '', ucwords(str_replace('_', ' ' , $this->mSaveHandler))) . 'SaveHandler';
            $file = GTFW_BASE_DIR_CORE . 'session/save_handler/' . $this->mSaveHandler . '/' . $save_handler_class . '.class.php';
            if(file_exists($file)){
                include GTFW_BASE_DIR_CORE . 'session/save_handler/SessionSaveHandlerIntf.intf.php';
                include $file;
                $this->mSaveHandlerObj = new $save_handler_class();
                session_set_save_handler(
                    array($this->mSaveHandlerObj, 'SessionOpen'),
                    array($this->mSaveHandlerObj, 'SessionClose'),
                    array($this->mSaveHandlerObj, 'SessionRead'),
                    array($this->mSaveHandlerObj, 'SessionWrite'),
                    array($this->mSaveHandlerObj, 'SessionDestroy'),
                    array($this->mSaveHandlerObj, 'SessionGc')
                );
            }
        }

        return true;
    }
    ?>
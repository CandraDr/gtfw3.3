.. _gtfwsession-start:

Start()
=======

.. raw:: html

    <details>
    <summary>Source code fungsi Start()</summary>

.. code-block:: php
   :linenos: 
   :caption: Source code @main/system/core/session/GtfwSession.class.php

    <?php
    public function Start($forceNew = true){
        if($this->mSessionIsStarted){
            if($forceNew)$this->End();
            else return $this->mSessionIsStarted;
        }
        
        $session_cookie_param = $this->mCookieParam;
        ini_set('session.gc_maxlifetime', $session_cookie_param['lifetime']);

        $session_expired = FALSE;
        if(isset($_COOKIE[$this->mName])){
            if($this->mSaveHandler === 'default'){
                $filename = ($this->mId != '')?$this->mId:$_COOKIE[$this->mName];
                $session_file = $this->mSavePath . 'sess_' . $filename;
                if(file_exists($session_file)){
                    $last_modified = $_SERVER['REQUEST_TIME'] - filemtime($session_file);
                    if($last_modified > $this->mExpire){
                        $session_expired = TRUE;
                    }
                }else{
                    $session_expired = TRUE;
                }
            }else{
                if(isset($this->mSaveHandlerObj))$session_expired = $this->mSaveHandlerObj->IsSessionExpired($_COOKIE[$this->mName]);
            }

            if($session_expired){ // regenerate session id
                $_COOKIE = null;
                unset($_COOKIE[$this->mName]);
            }
        }

        $session_cookie_param['path'] = $this->mBaseDir;
        session_set_cookie_params(
            0, // always zero, to prevent cookie timing difference
            $session_cookie_param['path'],
            isset($session_cookie_param['domain'])?$session_cookie_param['domain']:'',
            isset($session_cookie_param['secure'])?$session_cookie_param['secure']:''
        );

        if(session_start()){
            $this->mSessionIsStarted = TRUE;
            $this->mId = session_id();
        }else{
            die("session can't start");
        }
        return $this->mSessionIsStarted;
    }
    ?>

.. raw:: html

    </details>
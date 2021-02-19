.. raw:: html

    <details>
    <summary>Full source code Gtfw Cpu</summary>

.. code-block:: php
   :linenos: 
   :caption: Source code @main/system/core/session/GtfwSession.class.php

    <?php
    class GtfwSession extends GtfwBaseSingleton{
        private $mSaveHandlerObj = array();
        private $mCookieParam = array();
        private $mName = '';
        private $mExpire = '';
        private $mId = '';
        private $mSaveHandler = '';
        private $mSessionDir = '';
        private $mBaseDir = '';
        private $mSavePath = false;
        private $mSessionIsStarted = false;
        private $mMultiUser = false;
        
        public function Name(){
            return $this->mName;
        }

        public function SavePath(){
            return $this->mSavePath;
        }

        public function IsStarted() {
            return $this->mSessionIsStarted;
        }

        public function Restart(){
            $res = session_regenerate_id(TRUE);
            $this->mId = session_id();
            return $res;
        }

        public function Close(){
            session_write_close();
            $this->mSessionIsStarted = FALSE;
        }

        public function End($destroySession = TRUE){
            if($this->mSessionIsStarted){
                if($destroySession){
                    if(isset($_COOKIE[$this->mName])){
                        $session_cookie_param = $this->mCookieParam;
                        $session_cookie_param['path'] = $this->mBaseDir;
                        
                        setcookie(
                            $this->mName, '',
                            time() - $this->mExpire - 42000,
                            $session_cookie_param['path'],
                            isset($session_cookie_param['domain'])?$session_cookie_param['domain']:'',
                            isset($session_cookie_param['secure'])?$session_cookie_param['secure']:''
                        );
                    }
                }
                session_unset();
                session_destroy();
                $this->Close();
            }
            return $this->mSessionIsStarted;
        }

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
        // backward compatibility, deprecated soon
    }
    ?>

.. raw:: html

    </details>
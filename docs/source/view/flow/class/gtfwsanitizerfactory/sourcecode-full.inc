.. raw:: html

    <details>
    <summary>Full source code GtfwSanitizerFactory</summary>

.. code-block:: php
   :linenos: 
   :caption: Source code @main/system/core/sanitizer/GtfwSanitizerFactory.class.php

    <?php
    /**
    GtfwSanitizerFactory
        class baru sebagai factory variable,
        masih mengikuti old version => object return style, deprecated soon

    @author 	:	Wahyu A.Y

    @modified	:
    @copyright 2014 Gamatechno
    */

    class GtfwSanitizerFactory extends GtfwBase implements Countable, ArrayAccess, Iterator{
        protected $mInitialized = false;
        private $currentIndex = 0;
        private $mCompound;
        private $mRaw;

        public static function Wrap($compound, $skipSanitize = false) {
            $vb = new GtfwSanitizerFactory();
            $vb->DoInit($compound, $skipSanitize);
            unset($compound);

            return $vb;
        }

        public function AsArray($autoSanitize = true){
            // if($autoSanitize){
            // 	$result = $this->getAsArray($this->mCompound);
            // }else{
            // 	$result = $this->mRaw;
                /**
                *this is used for developer get primitive value of request method, 
                *but any filter for data contain quote(') to be (\')
                */
                /*this is rollback*/
                //$result = $this->AsArrayFalseAutoSanitize($this->mRaw);
            // }
            $result = $this->getAsArray($this->mCompound);
            return $result;
        }

        /**
        *@descryption AsArray process with false autoSanitize params
        *@author imaduddin@ecampuz.com
        */
        private function AsArrayFalseAutoSanitize($req){
            $result = array();
            if (!empty($req)){
                foreach ($req as $key => $value) {
                    if (is_array($value)){
                        /**
                        * recursive process when array value
                        */
                        $result[$key] = $this->AsArrayFalseAutoSanitize($value);
                    }else{
                        $result[$key] = str_replace(array("'"), array("\'"), $value);
                    }
                }
            }
            return $result;
        }

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

        private function get($varName = null){
            if(isset($varName)){
                if(isset($this->mCompound)){
                    if(isset($this->mCompound[$varName])){
                        if(is_array($this->mCompound[$varName]) or is_object($this->mCompound[$varName]))return $this->mCompound[$varName];
                        else return $this->mCompound[$varName];
                    }
                    else return GtfwSanitizerFactory::Wrap(null, true);
                }else return GtfwSanitizerFactory::Wrap(null, true);
            }else return $this->mCompound;
        }

        private function Sanitize($compound){
            if(is_array($compound)){
                $result = array();

                foreach($compound as $key => $value){
                    $result[$key] = $this->Sanitize($value);
                }
            }else{
                $compound = GtfwCpu::$system->GtfwSanitizer->PregReplace($compound);
                $result = GtfwSanitizerFactory::Wrap($compound, true);
                // $result = GtfwCpu::$system->GtfwSanitizer->PregReplace($compound);
            }

            return $result;
        }

        private function getAsArray($compound){
            if(is_array($compound)){
                $result = array();

                foreach($compound as $key => $value){
                    $result[$key] = $this->getAsArray($value);
                    // if (in_array($key, $arrSanitizerException)) $result[$key] = $value;
                    // else $result[$key] = GtfwCpu::$system->GtfwSanitizer->encodeTags($value);
                }
            }else{
                // $result = $compound->Raw();
                $result = GtfwCpu::$system->GtfwSanitizer->PregReplace($compound);
            }

            return $result;
        }

        public function IsArray() {
            return FALSE;
        }

        public function Raw() {
            return $this->mRaw;
        }

        public function Integer(){
            $this->mCompound = (int)$this->mCompound;
            return $this;
        }

        public function Float($min = '', $max = ''){
            $this->mCompound = (float)$this->mCompound;
            return $this;
        }


        //===== MAGIC METHOD FROM COUNTABLE
        public function offsetExists($offset){
            return isset($this->mCompound[$offset]);
        }

        public function offsetGet($offset){
            return $this->get($offset);
        }

        function offsetSet($offset,$value){
            $this->mCompound[$offset] = $value;
        }

        function offsetUnset($offset){
            unset($this->mCompound[$offset]);
        }

        //Region Countable
        function count(){
            return count(array_keys($this->mCompound));
        }
        //EndRegion

        //Region Iterator
        function current(){
            $dummy = array_keys($this->mCompound);
            return $this->offsetGet($dummy[$this->currentIndex]);
        }

        function key(){
            $dummy = array_keys($this->mCompound);
            return $dummy[$this->currentIndex];
        }

        function next(){
            $dummy = array_keys($this->mCompound);

            if ($this->currentIndex < count($dummy))
                $this->currentIndex++;

            return $this->currentIndex;
        }

        function rewind(){
            $this->currentIndex = 0;
        }

        function valid(){
            $dummy = array_keys($this->mCompound);
            if(isset($dummy[$this->currentIndex])){
                if($this->offsetExists($dummy[$this->currentIndex])) {
                    return true;
                } else {
                    return false;
                }
            }else 
            return false;
        }

        function append($value){
            $this->mCompound[] = $value;
        }

        function getIterator(){
            return $this;
        }
        //EndRegion
        
        public function __toString(){
            $return = '';
            if(isset($this->mCompound)){
                if (is_array($this->mCompound) || is_object($this->mCompound)){
                    $return = 'Array';
                }else if (is_null($this->mCompound)){
                    $return = '';
                }else{
                    $return = (String) $this->mCompound;
                }
            }
            return $return;
        }

        public function __call($method, $args){
            if(is_callable(array(GtfwCpu::$system->GtfwSanitizer, $method))){
                $compound = call_user_func_array(array(GtfwCpu::$system->GtfwSanitizer, $method), array($this->mRaw));
                return GtfwSanitizerFactory::Wrap($compound, true);
            }
        }
    }
    ?>

.. raw:: html

    </details>

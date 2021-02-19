.. _benchmark:

****************
Simple Benchmark
****************

.. raw:: html

    <details>
    <summary>Full source code Benchmark</summary>

.. code-block:: php
   :linenos: 
   :caption: Source code @main/system/libraries/simple_benchmark/SimpleBenchmark.class.php

    <?php
    class SimpleBenchmark {
        private static $mrInstance;
        private $result = array('time' => array(),'memory' => array(), 'memory_unconvert' => array());

        public function start() {
            $this->result['time'][0] = microtime(true);
            $this->result['memory'][0] = memory_get_peak_usage();
            $this->result['memory_unconvert'][0] = $this->result['memory'][0];
        }

        function convert($size) {
            $unit=array('b','kb','mb','gb','tb','pb');
            return @round($size/pow(1024,($i=floor(log($size,1024)))),2).' '.$unit[$i];
        }
        
        public function stop() {
            $this->result['time'][1] = microtime(true);
            $this->result['memory'][1] = memory_get_peak_usage();
            $this->result['memory_unconvert'][1] = $this->result['memory'][1];
        }
        
        public function result() {
            return array(
                'time'              => $this->result['time'][1] - $this->result['time'][0],
                'memory'            => $this->convert($this->result['memory'][1] - $this->result['memory'][0]),
                'memory_unconvert'  => ($this->result['memory_unconvert'][1] - $this->result['memory_unconvert'][0])
            );
        }
        
        public static function Instance() {
            return self::$mrInstance;
        }

        public static function Initialize(){
            self::$mrInstance = new SimpleBenchmark();
        }
        
        private function __construct(){}
    }
    ?>

.. raw:: html

    </details>

.. _benchmark-initialize:

Initialize()
============

Inisialisasi object baru dari class SimpleBenchmark.

.. code-block:: php
   :linenos: 
   :caption: Source code @main/system/libraries/simple_benchmark/SimpleBenchmark.class.php

    <?php
    public static function Initialize(){
        self::$mrInstance = new SimpleBenchmark();
    }
    ?>

.. _benchmark-instance:

Instance()
==========

Mengembalikan property mrInstance yang sudah menjadi object dari fungsi :ref:`Initialize() <benchmark-initialize>`

.. code-block:: php
   :linenos: 
   :caption: Source code @main/system/libraries/simple_benchmark/SimpleBenchmark.class.php

    <?php
    public static function Instance() {
        return self::$mrInstance;
    }
    ?>

.. _benchmark-start:

start()
=======

Mulai proses benchmark dengan menyimpan waktu dan memory yang terpakai.

.. code-block:: php
   :linenos: 
   :caption: Source code @main/system/libraries/simple_benchmark/SimpleBenchmark.class.php

    <?php
    public function start() {
        $this->result['time'][0] = microtime(true);
        $this->result['memory'][0] = memory_get_peak_usage();
        $this->result['memory_unconvert'][0] = $this->result['memory'][0];
    }
    ?>
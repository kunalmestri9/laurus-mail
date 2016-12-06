<?php
import("com.laurus.core.mail.api.IHtmlMailGenerator");
/**
 * Description of MMailFormater
 *
 * @author Kunal Mestri <kunal@laurus-it.com>
 */
class MailFormater implements IHtmlMailGenerator {
    
    private $parentTmpl;
    private $childTmpl;
    private $entries;
    
    
    public function __construct() {
        $this->entries=new SimpleList();
    }
    
    public function getHTML() {
        $childStr="";
        for($i=0;$i<$this->entries->size();$i++){
           $htmlC= str_replace("%KEY",$this->entries->get($i)->getKey(),$this->childTmpl);
           $htmlC= str_replace("%VALUE",$this->entries->get($i)->getValue(),$htmlC);
           $childStr.=$htmlC;
        }
        return str_replace("?",$childStr,$this->parentTmpl);
    }    
    public function addEntry($key,$value) {
        $this->entries->add(new Entry($key,$value));
    }
    public function getParentTmpl() {
        return $this->parentTmpl;
    }

    public function setParentTmpl($parentTmpl) {
        $this->parentTmpl = $parentTmpl;
    }

    public function getChildTmpl() {
        return $this->childTmpl;
    }

    public function setChildTmpl($childTmpl) {
        $this->childTmpl = $childTmpl;
    }

}

?>

<?php
import("com.laurus.core.mail.api.IMail");
/**
 * Description of AbstractMail
 *
 * @author Kunal Mestri <kunal@laurus-it.com>
 */
abstract class AbstractMail implements IMail{
    protected $bcc;
    protected $cc;
    protected $from;
    protected $subject;
    protected $to;
    protected $content;
    protected $contentType;
    protected $array;
    protected $priority;
    
    public function __construct() {
        $this->array=array();
    }

    public function setBcc($bcc) {
        $this->bcc=$bcc;
    }
    public function setFrom($from) {
        $this->from=$from;
    }
    public function setCc($cc) {
        $this->cc=$cc;
    }
    public function setSubject($subject) {
        $this->subject=$subject;
    }
    public function setTo($to) {
        $this->to=$to;
    }
    
    public function getBcc() {
        return $this->bcc;
    }
    public function getCc() {
        return $this->cc;
    }
    public function getFrom() {
        return $this->from;
    }
    public function getSubject() {
        return $this->subject;
    }
    public function getTo() {
        return $this->to;
    }
    public function setContent($content) {
        $this->content=$content;
    }
    public function getContent() {
        return $this->content;
    }

    public function setPriority($priority) {
        $this->priority=$priority;
    }

    public function getContentType() {
        if($this->isAttachmentPresent()){
            return IMailType::MIXED;
        }
        return $this->getType();
    }

    public function getPriority() {
        return $this->priority;
    }
    public function addAttachment($fullfilepath) {
        return array_push($this->array, $fullfilepath);
    }
    
    public function getAllAttachment() {
        return $this->array;
    }
    public function setContentType($contentType) {
         $this->contentType;
    }
    public function isAttachmentPresent() {
        return (count($this->array)!=0);
    }
}

?>

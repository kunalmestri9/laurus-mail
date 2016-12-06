<?php
/**
 *
 * @author Kunal Mestri <kunal@laurus-it.com>
 */
interface IMail {
    public function setSubject($subject);
    public function setCc($cc);
    public function setBcc($bcc);
    public function setTo($to);
    public function setFrom($from);
    public function getSubject();
    public function getCc();
    public function getBcc();
    public function getTo();
    public function getFrom();
    public function setContentType($contentType);
    public function getContentType();
    public function setContent($content);
    public function getContent();
    public function setPriority($priority);
    public function getPriority();
    public function addAttachment($fullfilepath);
    public function getAllAttachment();
    public function getType();
    
    
}

?>

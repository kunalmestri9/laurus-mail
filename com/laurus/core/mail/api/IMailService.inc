<?php
import("com.laurus.core.services.IService");
/**
 *
 * @author Kunal Mestri <kunal@laurus-it.com>
 */
interface IMailService extends IService{
    const NAME="MAIL_SERVICE";
    const HTML_MAIL_CLASS="HTML_MAIL_CLASS";
    const PLAIN_MAIL_CLASS="PLAIN_MAIL_CLASS";
    public function send(IMail $mail);
    public function getHTMLMail();
    public function getPlainMail();
}

?>

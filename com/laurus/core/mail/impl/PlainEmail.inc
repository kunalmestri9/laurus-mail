<?php
/**
 * Description of PlainEmail
 *
 * @author Kunal Mestri <kunal@laurus-it.com>
 */
import("com.laurus.core.mail.api.IMailType");
import("com.laurus.core.mail.impl.AbstractMail");

class PlainEmail extends AbstractMail {
    public function getType() {
        return IMailType::TEXT;
    }   
}

?>

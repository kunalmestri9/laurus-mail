<?php
/**
 * Description of HtmlMail
 *
 * @author Kunal Mestri <kunal@laurus-it.com>
 */
import("com.laurus.core.mail.api.IHtmlMailGenerator");
import("com.laurus.core.mail.api.IMailType");
import("com.laurus.core.mail.impl.AbstractMail");
class HtmlMail extends AbstractMail{
    public final function getType() {
        return IMailType::HTML;
    }
    public function setHTML($html) {
        $this->setContent($html);
    }
    public function setHTMLGenerator(IHtmlMailGenerator $gen) {
        $this->setContent($gen->getHTML());
    }
}


?>

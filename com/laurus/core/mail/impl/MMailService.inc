<?php
import("com.laurus.core.mail.api.IMailService");
/**
 * Description of MMailService
 *
 * @author Kunal Mestri <kunal@laurus-it.com>
 */
class MMailService implements IMailService{
    private $logger;
    private static $instance;
    protected $htmlMailClass;
    protected $plainTextClass;
    
    
    public function __construct() {
        $this->logger=Logger::getLogger(__CLASS__);
    }
    public function getHTMLMail() {
        return ClassLoader::loadName($this->htmlMailClass)->getInstance();
    }

    public function getPlainMail() {
        return ClassLoader::loadName($this->plainTextClass)->getInstance();
    }

    public function send(\IMail $mail) {
         $result=($mail->getContentType()==IMailType::MIXED)?$this->sendMailWithAttachment($mail):$this->sendMail($mail);
         $resultString=($result)?"Mail is send successfully":"Mail Sending Failed";
         $this->logger->debug($resultString);
         return $result;
    }
    
    protected function sendMailWithAttachment(\IMail $mail){
        $to = $mail->getTo();
        $this->logger->debug("Sending Mail To :".$to);
        $subject =$mail->getSubject(); 
        $this->logger->debug("Subject :" . $subject);
        $headers = "From: ".$mail->getFrom();
        $this->logger->debug("From:  :" . $mail->getFrom());
        if($mail->getCc()!=NULL){
            $this->logger->debug("CC:  :" . $mail->getCc());
            $headers .= "Cc:".$mail->getCc();
        }
        if($mail->getBcc()!=NULL){
            $this->logger->debug("Bcc:  :" . $mail->getBcc());
            $headers .= "Bcc:".$mail->getBcc();
        }
        // boundary 
        $mime_boundary =md5(uniqid(time())); 
        // headers for attachment 
        $headers .= "\nMIME-Version: 1.0\n" . "Content-Type: ".IMailType::MIXED.";\n" . " boundary=\"{$mime_boundary}\""; 
        // multipart boundary 
        $message = "This is a multi-part message in MIME format.\n\n" . "--{$mime_boundary}\n" ;
        $message .="Content-Type: ".$mail->getType() ."; charset=\"iso-8859-1\"\n" . "Content-Transfer-Encoding: 7bit\n\n" . $mail->getContent() . "\n\n"; 
        $message .= "--{$mime_boundary}\n";
        
        // preparing attachments 
        $files=$mail->getAllAttachment();
        for($x=0;$x<count($files);$x++){
                $this->logger->debug("Attaching File : " .$files[$x]);
                $file = fopen($files[$x],"rb");
                $data = fread($file,filesize($files[$x]));
                fclose($file);
                $data = chunk_split(base64_encode($data));
                $message .= "Content-Type: {\"application/octet-stream\"};\n" . " name=\"$files[$x]\"\n" . 
                "Content-Disposition: attachment;\n" . " filename=\"$files[$x]\"\n" . 
                "Content-Transfer-Encoding: base64\n\n" . $data . "\n\n";
                $message .= "--{$mime_boundary}\n";
                $this->logger->debug("File Attached : " .$files[$x]);
        }
        // send mail
        $this->logger->debug("Sending Mail");
        return @mail($to, $subject, $message, $headers); 
    }
    protected function sendMail(IMail $mail){
        /**
         * @todo SET PRIORITY, REPLY TO
         */
        $to = $mail->getTo(); 
        $this->logger->debug("Sending Mail To :".$to);
        $from = $mail->getFrom();
        $this->logger->debug("From:  :" . $mail->getFrom());
        $subject = $mail->getSubject();
        $this->logger->debug("Subject :" . $subject);
        $message=$mail->getContent();
        $this->logger->debug("content  :" . $mail->getContent());
        $headers  = "From: $from\r\n"; 
        $headers .= "Content-type: ".$mail->getType()."\r\n"; 
        if($mail->getCc()!=NULL)
            $headers .= "Cc:".$mail->getCc();
        if($mail->getBcc()!=NULL)
            $headers .= "Bcc:".$mail->getBcc();
        return mail($to, $subject, $message, $headers);
    }
    
    
    public function init(\IServiceConfig $config) {
        $this->htmlMailClass=$config->getConfigParameter(IMailService::HTML_MAIL_CLASS);
        $this->plainTextClass=$config->getConfigParameter(IMailService::PLAIN_MAIL_CLASS);
    }

    public static function getInstance() {
        if(self::$instance==null){
            self::$instance=new MMailService();
        }
        return self::$instance;
    } 
    
}

?>

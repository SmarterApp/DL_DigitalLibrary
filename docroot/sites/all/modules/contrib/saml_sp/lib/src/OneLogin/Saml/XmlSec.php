<?php

/**
 * Determine if the SAML response is valid using a provided x509 certificate.
 */
class OneLogin_Saml_XmlSec
{
    /**
     * A SamlResponse class provided to the constructor.
     * @var OneLogin_Saml_Settings
     */
    protected $_settings;

    /**
     * The document to be tested.
     * @var DomDocument
     */
    protected $_document;

    /**
     * Construct the SamlXmlSec object.
     *
     * @param OneLogin_Saml_Settings $settings A SamlResponse settings object containing the necessary
     *                                          x509 certicate to test the document.
     * @param OneLogin_Saml_Response $response The document to test.
     */
    public function __construct(OneLogin_Saml_Settings $settings, OneLogin_Saml_Response $response)
    {
        $this->_settings = $settings;
        $this->_document = clone $response->document;
    }

    /**
     * Verify that the document only contains a single Assertion
     *
     * @return bool TRUE if the document passes.
     */
    public function validateNumAssertions()
    {
        $rootNode = $this->_document;
        $assertionNodes = $rootNode->getElementsByTagName('Assertion');
        return ($assertionNodes->length == 1);
    }

    /**
     * Verify that the document is still valid according
     *
     * @return bool
     */
    public function validateTimestamps()
    {
        $rootNode = $this->_document;
        $timestampNodes = $rootNode->getElementsByTagName('Conditions');
        for ($i = 0; $i < $timestampNodes->length; $i++) {
            $nbAttribute = $timestampNodes->item($i)->attributes->getNamedItem("NotBefore");
            $naAttribute = $timestampNodes->item($i)->attributes->getNamedItem("NotOnOrAfter");
            if ($nbAttribute && strtotime($nbAttribute->textContent) > time()) {
                return false;
            }
            if ($naAttribute && strtotime($naAttribute->textContent) <= time()) {
                return false;
            }
        }
        return true;
    }

    /**
     * @return bool
     * @throws Exception
     */
    public function isValid()
    {
        $objXMLSecDSig = new XMLSecurityDSig();
      error_log("valid1");
        $objDSig = $objXMLSecDSig->locateSignature($this->_document);
        if (!$objDSig) {
          error_log("invalid1");
            throw new Exception('Cannot locate Signature Node');
        }
        $objXMLSecDSig->canonicalizeSignedInfo();
        $objXMLSecDSig->idKeys = array('ID');
      error_log("valid12");
        $retVal = $objXMLSecDSig->validateReference();
        if (!$retVal) {
          error_log("invalid12");
            throw new Exception('Reference Validation Failed');
        }
      error_log("valid13");
        $singleAssertion = $this->validateNumAssertions();
        if (!$singleAssertion) {
          error_log("invalid13");
            throw new Exception('Multiple assertions are not supported');
        }
      error_log("valid14");
        $validTimestamps = $this->validateTimestamps();
        if (!$validTimestamps) {
          error_log("invalid14");
            throw new Exception('Timing issues (please check your clock settings)
            ');
        }
      error_log("valid15");
        $objKey = $objXMLSecDSig->locateKey();
        if (!$objKey) {
          error_log("invalid15");
            throw new Exception('We have no idea about the key');
        }
      error_log("valid16");
        XMLSecEnc::staticLocateKeyInfo($objKey, $objDSig);

        $objKey->loadKey($this->_settings->idpPublicCertificate, FALSE, TRUE);
      error_log("valid17");

      if ($objXMLSecDSig->verify($objKey)) {
        error_log("valid18");
        return true;
      }
      else {
        error_log("valid19");
        return false;
      }


    }
}
<?php

use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalDriverManager;
use Behat\Mink\Exception\ExpectationException;
use Drupal\DrupalExtension\Context\MinkContext;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;

class ChosenContext implements DrupalSubContextInterface {

  private $drupal;
  protected $last_id;

  /** @var MinkContext */
  private $minkContext;

  public function __construct(DrupalDriverManager $drupal) {
    $this->drupal = $drupal;
  }

  /** @BeforeScenario */
  public function gatherContexts(BeforeScenarioScope $scope) {
    $environment = $scope->getEnvironment();
    $this->minkContext = $environment->getContext('Drupal\DrupalExtension\Context\MinkContext');
  }

  /**
   * @return MinkContext
   */
  public function getMinkContext() {
    return $this->minkContext;
  }

  /**
   * @When /^I the set the chosen element "([^"]*)" to "([^"]*)"$/
   */
  public function iSetChosenElement($locator, $value) {
    $session = $this->getMinkContext()->getSession();
    $el = $session->getPage()->findField($locator);

    if (empty($el)) {
      throw new ExpectationException(t('No such select element @locator ', array(
        '@value' => $value,
        '@locator' => $locator,
      )), $session);
    }

    $element_id = str_replace('-', '_', $el->getAttribute('id')) . '_chzn';

    $el =$session->getPage()->find('xpath', "//div[@id='{$element_id}']");

    if ($el->hasClass('chzn-container-single')) {
      // This is a single select element.
      $el = $session->getPage()->find('xpath', "//div[@id='{$element_id}']/a[@class='chzen-single']");
      $el->click();
    }
    elseif ($el->hasClass('chzn-container-multi')) {
      // This is a multi select element.
      $el = $session->getPage()->find('xpath', "//div[@id='{$element_id}']/ul[@class='chzn-choices']/li[@class='search-field']/input");
      $el->click();
    }

    $selector = "//div[@id='{$element_id}']/div[@class='chzn-drop']/ul[@class='chzn-results']/li[text() = '{$value}']";
    $el = $session->getPage()->find('xpath', $selector);

    if (empty($el)) {
      throw new ExpectationException(t('No such option @value in @locator ', array(
        '@value' => $value,
        '@locator' => $locator,
      )), $session);
    }

    $el->click();
  }

}
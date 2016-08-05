<?php

use Drupal\DrupalExtension\Context\MinkContext;
use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;
use Behat\Mink\Exception\ElementNotFoundException;

/**
 * Defines application features from the specific context.
 */
class FeatureContext extends RawDrupalContext implements SnippetAcceptingContext {
    /**
     * Initializes context.
     *
     * Every scenario gets its own context instance.
     * You can also pass arbitrary arguments to the
     * context constructor through behat.yml.
     */
    public function __construct() {
    }

    /**
     * @Then I wait for :seconds seconds
     *
     * @param $seconds
     *   integer The number of seconds to wait
     */
    public function iWaitForSeconds($seconds)
    {
      $seconds = $seconds * 1000;
      $this->getSession()->wait($seconds, false);
    }


    /**
     * @Then I wait for the :region region to Appear
     *
     * @param $region
     *   string The region that we want to see
     */
    public function iWaitForTheRegionToAppear($region)
    {
        $this->getSession()->wait(5000, "jQuery('{$region}').children().length > 0");
    }

    /**
     * @Then I wait for the :element element to Appear
     *
     * @param $element
     *   string The element that we want to see
     */
    public function iWaitForTheElementToAppear($element)
    {
        $this->getSession()->wait(20000, "jQuery('{$element}').length > 0");
    }

  /** Click on the element with the provided xpath query
   *
   * @When /^(?:|I )click on the element "([^"]*)"$/
   */
  public function iClickOnTheElement($locator)
  {
      $session = $this->getSession(); // get the mink session
      $element = $session->getPage()->find('css', $locator); // runs the actual query and returns the element
  
      // errors must not pass silently
      if (null === $element) {
          throw new \InvalidArgumentException(sprintf('Could not evaluate CSS selector: "%s"', $locator));
      }
  
      // ok, let's click on it
      $element->click();
  }
}

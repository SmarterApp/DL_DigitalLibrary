<?php

use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;

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
}

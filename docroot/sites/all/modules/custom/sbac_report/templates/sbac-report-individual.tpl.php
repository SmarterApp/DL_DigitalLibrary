<?php
/**
 * @file
 * Template for SBAC Individual Report page.
 */
?>
<h2 class="report-title"><?php print t('Individual Contributor and Reviewer Report'); ?></h2>
<div class="report-form-container"><?php print drupal_render($form); ?></div>
<hr />
<?php if ($error_message) : ?>
<?php print $error_message; ?>
<?php endif ?>

<?php if (!empty($sne_details) && !empty($contributed_summary)) : ?>
  <?php print $sne_details; ?>

  <h2><?php print t('Contributed Resources'); ?></h2>
  <div id="contributed-resources">
  <?php print $contributed_summary; ?>
  <?php if ($resource_statistics): ?>
    <h2>Feedback on Posted Resource(s)</h2>
    <p><?php print t('Thank you for contributing to the Digital Library. The
                  table below displays information about your posted resource(s).'); ?></p>
    <?php print $resource_statistics; ?>
  <?php endif; ?>
  <h2>Resource Submission Status</h2>
  <p><?php print t('The table below displays the status of your submitted resource(s).'); ?></p>
  <?php print $contributed_details; ?>
  </div>
  <div style="clear:both;"></div>
  <h2><?php print t('Resource Reviews'); ?></h2>
  <h3><?php print t('Gate-Keeping Reviews'); ?></h3>
  <p><?php print t('The table below includes decisions you made based
                  on the Gate-Keeping Criteria during the selected period of
                  time, including the resources you accepted and
                  moved forward to Quality Criteria Reviews and those you
                  returned to the contributor(s).'); ?></p>
  <?php print $gate_keeping; ?>

  <div style="clear:both;"></div>
  <h3><?php print t('Quality Criteria Reviews'); ?></h3>
  <p><?php print t('The table below includes the number of Quality Criteria Reviews
                    you have started but not yet completed,
                    and the total number Quality Criteria Reviews you have
                    completed in the selected time period.'); ?></p>
  <?php print $all_reviews; ?>
  <?php $help_link = l('help topics', 'help-topics') ;?>
  <h3><?php print t('Consistency Analysis of Quality Criteria Reviews'); ?></h3>
  <p><?php print t("Consistency rates compare a reviewer's posting recommendations
                    and Quality Criteria ratings to those of the other two reviewers
                    who reviewed the same resource. Rates for resources contributors
                    have resubmitted and rates for resources that have been removed
                    from the Digital Library are not displayed. See the !helplink
                    for more information.", array('!helplink' => $help_link) ); ?></p>
  <?php print $summation; ?>
<?php endif ?>

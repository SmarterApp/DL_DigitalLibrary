<?php
/**
 * @file
 * Template for SBAC Individual Report page.
 */
?>
<h2 class="report-title"><?php print t('Individual Contributor and Reviewer Report'); ?></h2>
<div class="report-form-container"><?php print drupal_render($form); ?></div>
<hr>
<?php if ($error_message) : ?>
<?php print $error_message; ?>
<?php endif ?>

<?php if (!empty($sne_details) && !empty($contributed_summary)) : ?>
  <?php print $sne_details; ?>

  <h2><?php print t('Contributed Resources'); ?></h2>
  <?php print $contributed_summary; ?>
  <?php print $contributed_details; ?>
  <div style="clear:both;"></div>
  <h2><?php print t('Resource Reviews'); ?></h2>
  <h3><?php print t('Gate-Keeping Reviews'); ?></h3>
  <p><?php print t('The table below includes decisions this reviewer made based
                  on the Gate-Keeping Criteria during the selected period of
                  time, including the resources the reviewer accepted and
                  moved forward to Quality Criteria Reviews and those the
                  reviewer returned to the contributor(s).'); ?></p>
  <?php print $gate_keeping; ?>

  <div style="clear:both;"></div>
  <h3><?php print t('All Reviews'); ?></h3>
  <p><?php print t('All consistency rates are calculated based on the
                    differential in recommendations or ratings between 3
                    resource reviewers. The tables below represent resources
                    for which all reviews were completed in the selected
                    time period.'); ?></p>
  <?php print $all_reviews; ?>
  <?php print $summation; ?>
<?php endif ?>

<?php
/* 
 * Template for SBAC landing page
 */
?>
<?php if($notifications): ?>
  <div id="lp-notifications-wrapper">
    <?php print $notifications; ?>
  </div>
<?php endif; ?>
<?php if($find_resource): ?>
  <div id="lp-find-resource-wrapper">
    <div id="lp-find-resource">
      <div id="lp-find-resource-lable">What resources are you looking for?</div>
      <?php print $find_resource; ?>
    </div>
  </div>
<?php endif; ?>
<?php if($featured_content): ?>
  <div id="lp-featured-content-wrapper">
    <div id="lp-featured-content">
      <?php print $featured_content; ?>
    </div>
  </div>
<?php endif; ?>
<?php if ($leaderboards): ?>
  <div id="leaderboard-wrapper">
    <div id="leaderboard-title">
      <h1>MOST ACTIVE MEMBERS</h1>    
    </div>
    <div id="leaderboards">
      <?php print $leaderboards; ?>
        <div id="sne-signup-spacer"></div>
        <div id="sne-signup">I am interested in contributing resources to the Digital Library <?php print l('Submit', '/sne-signup', array('attributes' => array('class' => array('button', 'sne-link')))); ?></div>
    </div>
  </div>
<?php endif; ?>
<?php if($help_topics): ?>
  <div id="lp-help-topics-wrapper">
    <div id="lp-help-topics" class="row">
      <?php print $help_topics; ?>
    </div>
  </div>
<?php endif; ?>

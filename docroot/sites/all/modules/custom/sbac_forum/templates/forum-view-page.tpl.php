<div class="sbac-forum-vp-controls-wrapper">
  <?php if (!empty($fields['controls_link_list']['markup']) ): ?>
    <div class="sbac-forum-vp-controls">
      <?php print t('Forum Settings');?>
    </div>
    <div class="sbac-forum-vp-controls-popup <?php print $fields['controls_link_list']['classes']; ?>">
      <?php print $fields['controls_link_list']['markup']; ?>
    </div>
  <?php endif;?>
</div>
<div class="sbac-forum-confirm-message-region">
  <?php if (!empty($fields['welcome_message'])) : ?>
      <div style="display:block">
        <?php print $fields['welcome_message']; ?>
      </div>
  <?php endif;?>
</div>

<div class="sbac-forum-vp-top clearfix">

  <div class="col narrow">

    <?php if ( !empty($fields['description']) ): ?>
      <div class="vp-desc-field">
        <?php print $fields['description']; ?>
      </div>
    <?php endif; ?>

    <?php if (!empty($fields['facilitators']) ): ?>
      <div class="vp-faci-field">
        <div class="title-tags"><?php print t('Facilitator(s):'); ?></div>
        <?php print $fields['facilitators'];?>
      </div>
    <?php endif;?>

  </div> <!-- End top-left-->


  <div class="col narrow">

    <?php if (!empty($fields['grades'])):?>
      <div class="vp-grades-field">
        <div class="title-tags"><?php print t('Grades'); ?></div>
        <?php print $fields['grades']; ?>
      </div>
    <?php endif; ?>

    <?php if (!empty($fields['subjects'])):?>
      <div class="vp-subjects-field">
        <div class="title-tags"><?php print t('Subjects and Domains'); ?></div>
        <?php print $fields['subjects']; ?>
      </div>
    <?php endif; ?>

  </div> <!-- End top-center-->


  <div class="col narrow">

    <?php if (!empty($fields['end_users'])):?>
      <div class="vp-end-users-field">
        <div class="title-tags"><?php print t('Intended End Users'); ?></div>
        <?php print $fields['end_users']; ?>
      </div>
    <?php endif; ?>

    <?php if (!empty($fields['students'])):?>
      <div class="vp-students-field">
        <div class="title-tags"><?php print t('Intended Student Populations'); ?></div>
        <?php print $fields['students']; ?>
      </div>
    <?php endif; ?>

  </div> <!-- End top-right-->

</div> <!--End top container -->

<div class="sbac-forum-vp-tabs">
  <?php print $fields['tabs']; ?>
</div>

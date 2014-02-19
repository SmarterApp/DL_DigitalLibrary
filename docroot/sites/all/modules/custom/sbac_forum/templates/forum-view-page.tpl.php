
<div class="sbac-forum-vp-controls">
  Forum Settings
</div>
<div class="sbac-forum-vp-top">

  <div class="top-left">

    <?php if ( !empty($fields['description']) ): ?>
      <div class="vp-desc-field">
        <?php print $fields['description']; ?>
      </div>
    <?php endif; ?>

    <?php if (!empty($fields['facilitators']) ): ?>
      <div class="vp-faci-field">
        <div class="title-tags"><?php print t('Facilitator(s)'); ?></div>
        <?php print $fields['facilitators'];?>
      </div>
    <?php endif;?>

  </div> <!-- End top-left-->


  <div class="top-center">

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


  <div class="top-right">

    <?php if (!empty($fields['end_users'])):?>
      <div class="vp-end-users-field">
        <div class="title-tags"><?php print t('Intended End Users'); ?></div>
        <?php print $fields['end_users']; ?>
      </div>
    <?php endif; ?>

    <?php if (!empty($fields['students'])):?>
      <div class="vp-students-field">
        <div class="title-tags"><?php print t('Intended Students'); ?></div>
        <?php print $fields['students']; ?>
      </div>
    <?php endif; ?>

  </div> <!-- End top-right-->

</div> <!--End top container -->

<div class="sbac-forum-vp-tabs">
  <?php print $fields['tabs']; ?>
</div>

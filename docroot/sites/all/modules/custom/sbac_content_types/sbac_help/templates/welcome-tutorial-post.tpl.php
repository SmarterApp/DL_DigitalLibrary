<div class="welcome-tutorial-back-button">
  <?php echo $back_link; ?>
</div>
<div class="welcome-tutorial-node-container">
  <div class="welcome-tutorial-node-title">
    <?php echo $title; ?>
  </div>
  <div class="welcome-tutorial-post-content">
  <?php if ($image): ?>
    <div class="tutorial-image">
      <?php echo $image; ?>
    </div>
  <?php endif; ?>
    <div class="tutorial-body-content">
      <?php echo $body; ?>
    </div>
  </div>
</div>

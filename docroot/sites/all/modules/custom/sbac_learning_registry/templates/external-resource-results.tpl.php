<?php foreach ($results as $result): ?>
  <?php if (!empty($result['name'])): ?>
    <div class="ex-resource-card">
      <div class="resource-title">
        <a href="<?php print $result['URL']; ?>" target="_blank"><?php print truncate_utf8($result['name'], 34, TRUE, TRUE); ?></a>
      </div>
      <div class="resource-content">
        <?php print truncate_utf8($result['description'], 184, TRUE, TRUE); ?>
      </div>
    </div>
  <?php endif; ?>
<?php endforeach; ?>
<?php print $load_more_link; ?>
<?php foreach ($results as $result): ?>
  <div>
    <div><a href="<?php print $result['URL']; ?>" target="_blank"><?php print $result['name']; ?></a></div>
    <div><?php print $result['description']; ?></div>
  </div>
<?php endforeach; ?>
<?php print $load_more_link; ?>
<?php $n = 1; ?>

<?php if ($sections): ?>
<div class="section-container auto" data-section>
<?php

  foreach ($sections as $key => $section):
  $user = $variables['user']->uid;
$node = node_load($section['nid']);
if ($section['id'] == 'section-gate-keeping-criteria-review' && $user == $node->uid && !in_array('administrator', $variables['user']->roles)) :

else :
?>
  <section class="specific-section <?php echo $section['class']; ?> <?php echo "section-" . $n; ?> ">
  <p class="title" data-section-title data-options="deep_linking: true">
  <a class="<?php echo $section['use-ajax']; echo ' ' . $section['section_loaded']; ?> section-link" section_id="<?php echo $section['id']; ?>" title="<?php echo $section['title']; ?>" href="/section-get-content/nojs?source=<?php echo $section['source']; ?>&tab=<?php echo $section['tab']; ?>&nid=<?php echo $section['nid']; ?>&section_id=<?php echo $section['id']; ?>"><?php echo $section['title']; ?></a>
</p>

<div id="<?php echo $section['id']; ?>" class="content" data-section-content>

<?php echo $section['content']; ?>
  </div>

  </section>
<?php

  endif;
$n++;

endforeach; ?>
</div>
<?php endif; ?>

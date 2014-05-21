<?php $n = 1; ?>
<?php if ($sections): ?>
<div class="section-container auto" data-section>
  <?php foreach ($sections as $key => $section): ?>
    <section class="<?php echo $section['class']; ?> <?php echo "section-" . $n; ?> ">
      <p class="title" data-section-title data-options="deep_linking: true">
        <a nid="<?php echo $section['nid']; ?>" section_id="<?php echo $section['class']; ?>" source="<?php echo $section['source']; ?>" tab="<?php echo $section['tab']; ?>" title="<?php echo $section['title']; ?>" href="#<?php echo $name . '-' . $key; ?>"><?php echo $section['title']; ?></a>
      </p>
      <div id="<?php echo $section['class']; ?>" class="content" data-section-content>
        <?php echo $section['content']; ?>
      </div>
    </section>
    <?php $n++; ?>
  <?php endforeach; ?>
</div>
<?php endif; ?>


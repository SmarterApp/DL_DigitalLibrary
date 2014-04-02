<?php $n = 1; ?>
<?php if ($sections): ?>
<div class="section-container auto" data-section>
  <?php foreach ($sections as $key => $section): ?>
    <section class="<?php echo $section['class']; ?> <?php echo "section-" . $n; ?> ">
      <p class="title" data-section-title data-options="deep_linking: true">
        <a title="<?php echo $section['title']; ?>" href="#<?php echo $name . '-' . $key; ?>"><?php echo $section['title']; ?></a>
      </p>
      <div class="content" data-section-content>
        <?php echo $section['content']; ?>
      </div>
    </section>
    <?php $n++; ?>
  <?php endforeach; ?>
</div>
<?php endif; ?>


<?php
/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
?>

<div class="slide featured-content-wrapper">
  <div class="featured-content-inner" url="<?php print $path ?>">
    <div class="col-resource">
      <?php if($thumbnail):?>
        <a href="/<?php print $path ?>">
          <div class="featured-resource-image" style="background-image: url(<?php print $thumbnail; ?>)"></div>
        </a>
      <?php endif; ?>
      <p class="featured-label featured-type">Featured Resource</p>
      <?php if($title):?>
        <div class="featured-resource-title featured-title">
          <a href="/<?php print $path ?>"><?php print $title; ?></a>
        </div>
      <?php endif;?>
      <?php if($mini_profile):?>
        <div class="featured-resource-mini-profile featured-mini-profile">
          <?php print $mini_profile; ?>
        </div>
      <?php endif; ?>
    </div>
    <div class="col-details">
      <?php if($summary):?>
        <div class="featured-resource-summary featured-summary">
          <?php print $summary; ?>
        </div>
      <?php endif; ?>
      <?php if($grades):?>
        <div class="featured-content-terms-wrapper featured-resource-grades featured-grades">
          <p class="featured-label">Grades</p>
          <?php print $grades; ?>
        </div>
      <?php endif; ?>
      <?php if($formative_process):?>
        <div class="featured-content-terms-wrapper featured-resource-formative featured-formative">
          <p class="featured-label">Formative Attributes</p>
          <?php print $formative_process; ?>
        </div>
      <?php endif; ?>
    </div>
  </div>
</div>

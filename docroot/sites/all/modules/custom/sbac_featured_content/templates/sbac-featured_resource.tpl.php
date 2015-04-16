<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
?>
<div class="featured-content-wrapper featured-resource-wrapper">
  <a href="<?php print $link;?>" class="featured-content-url featured-resource-url">
      <div class="col-resource">
        <?php if($thumbnail):?>
          <div class="featured-resource-image" style="background-image: url(<?php print $thumbnail; ?>)">
          </div>
        <?php endif; ?>
          <p class="featured-label featured-type">Featured Resource</p>
          <?php if($title):?>
            <div class="featured-resource-title featured-title">
              <?php print $title; ?>
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
  </a>
</div>
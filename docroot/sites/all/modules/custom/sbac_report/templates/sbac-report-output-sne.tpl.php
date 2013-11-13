<!-- Copied the view template that was being used before to minimize the theming effort -->
<div class="view view-sne-details view-id-sne_details view-display-id-sne_details">
  <div class="view-content">
    <div class="views-row views-row-1 views-row-odd views-row-first views-row-last">
      <div class="row first">
        <div>
          <div class="column large-3 profile-pic">
            <div class="user-picture">
              <?php
                if (isset($user_output['picture'])) {
                  print $user_output['picture'];
                }
              ?>
            </div>
          </div>
        </div>
        <div class="column large-9 user-profile">
          <div class="views-field views-field-field-first-name">
            <h2 class="field-content name clearfix">
              <?php
                if (isset($user_output['first_name'])) {
                  print $user_output['first_name'] . ' ';
                }
                if (isset($user_output['last_name'])) {
                  print $user_output['last_name'];
                }
              ?>
            </h2>
          </div>
          <div class="views-field views-field-nothing-3">
            <span class="field-content">
              <?php
                if (isset($user_output['position'])) {
                  print $user_output['position'] . ' from ';
                }
                if (isset($user_output['state'])) {
                  print $user_output['state'];
                }
              ?>
            </span>
          </div>
          <div class="profile-details">

            <?php if (isset($user_output['grade_level'])) : ?>
            <div class="views-field views-field-nothing">
              <span class="field-content">
                <div>
                  <span class="title">Grades: </span>
                  <?php
                    print implode(', ', $user_output['grade_level']);
                  ?>
                </div>
              </span>
            </div>
            <?php endif; ?>

            <?php if (isset($user_output['subjects'])) : ?>
            <div class="views-field views-field-nothing-1">
              <span class="field-content">
                <div>
                  <span class="title">Subjects: </span>
                  <?php
                    print implode(', ', $user_output['subjects']);
                  ?>
                </div>
              </span>
            </div>
            <?php endif; ?>

            <?php if (isset($user_output['populations'])) : ?>
            <div class="views-field views-field-nothing-2">
              <span class="field-content">
                <div>
                  <span class="title">Student Populations: </span>
                    <?php print implode(', ', $user_output['populations']); ?>
                </div>
              </span>
            </div>
            <?php endif; ?>
          </div>
        </div>
      </div>
    </div>
  </div>
</div>

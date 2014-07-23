<div class="row first">
    <div class="column large-3 profile-pic">
      <?php
        echo $profile_picture;
      ?>
    </div>

  <div class="column large-9 user-profile">
    <div class="name clearfix">
      <?php echo $first_name . ' '; ?>
      <?php echo $last_name; ?>
    </div>

    <div class="profile-title">
      <?php echo $title; ?>
    </div>

    <div class="profile-school">
      <span class="profile-school-name">
        <?php echo $school; ?>
      </span>
      <?php
        echo $district;
        echo (($school || $district) && $state)? ', ' : '';
        echo $state;
      ?>
    </div>

    <div class="profile-email-address">
      <?php
        echo $email;
      ?>
    </div>

      <div class="introduction">
        <?php echo $about; ?>
      </div>
      <div class="profile-details">
        <?php
          echo '<div><span class="title">Grades: </span>'. $grades .'</div>';
          echo '<div><span class="title">Subjects: </span>'. $subjects .'</div>';
          echo '<div><span class="title">Student Populations: </span>'. $population .'</div>';
        ?>
      </div>


  </div>


</div> <!-- END row first-->
<div class="line"></div>
<div class="row second">
  <div class="column large-12">
    <?php
      if (isset($user_profile['sections'])) {
        echo theme('sections', array(
          'sections' => $user_profile['sections'],
          'name' => 'profile',
        ));
      }
    ?>
  </div>

</div>

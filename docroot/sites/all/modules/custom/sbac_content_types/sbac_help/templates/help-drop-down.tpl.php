<div class="help-dropdown">
    <a  data-dropdown="drop1" href="#" title="Help"><span class="sbac-question"></span> Help</a>
    <ul id="drop1" class="f-dropdown" data-dropdown-content>
        <li><a class='sbac-help-welcome-tutorial-modal' title='Welcome Tutorial' href="#" class="help-modal">Welcome Tutorial</a></li>
        <li><?php print l(t('Glossary'), 'glossary', array('absolute' => TRUE, 'attributes' => array('title' => 'Glossary'))); ?></li>
        <li><a title='Help Topics' href="/help-topics">Help Topics</a></li>
    </ul>
</div>
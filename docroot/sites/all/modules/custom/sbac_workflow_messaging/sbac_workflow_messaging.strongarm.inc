<?php
/**
 * @file
 * sbac_workflow_messaging.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function sbac_workflow_messaging_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_78306_criteria_1_description';
  $strongarm->value = array(
    'value' => '<p><span style="line-height: 16px;">a. The Rationale section of the Educator Learning Guide is clear and well-organized. It:</span></p><p><span style="line-height: 16px;">&nbsp; i. identifies a Playlist topic that accurately reflects the intent of the Common Core State Standards, other nationally recognized content standards, or other state specific standards.</span></p><p><span style="line-height: 16px;">&nbsp; ii. explains why the Playlist topic is important</span></p>',
    'format' => 'full_html',
  );
  $export['qc_78306_criteria_1_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_78306_criteria_1_desc_state';
  $strongarm->value = 'collapsed';
  $export['qc_78306_criteria_1_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_78306_criteria_1_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_78306_criteria_1_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_78306_criteria_1_title';
  $strongarm->value = array(
    'value' => '<p><!--[if gte mso 9]><xml>
 <w:WordDocument>
  <w:View>Normal</w:View>
  <w:Zoom>0</w:Zoom>
  <w:TrackMoves/>
  <w:TrackFormatting/>
  <w:PunctuationKerning/>
  <w:ValidateAgainstSchemas/>
  <w:SaveIfXMLInvalid>false</w:SaveIfXMLInvalid>
  <w:IgnoreMixedContent>false</w:IgnoreMixedContent>
  <w:AlwaysShowPlaceholderText>false</w:AlwaysShowPlaceholderText>
  <w:DoNotPromoteQF/>
  <w:LidThemeOther>EN-US</w:LidThemeOther>
  <w:LidThemeAsian>X-NONE</w:LidThemeAsian>
  <w:LidThemeComplexScript>X-NONE</w:LidThemeComplexScript>
  <w:Compatibility>
   <w:BreakWrappedTables/>
   <w:SnapToGridInCell/>
   <w:WrapTextWithPunct/>
   <w:UseAsianBreakRules/>
   <w:DontGrowAutofit/>
   <w:SplitPgBreakAndParaMark/>
   <w:EnableOpenTypeKerning/>
   <w:DontFlipMirrorIndents/>
   <w:OverrideTableStyleHps/>
  </w:Compatibility>
  <m:mathPr>
   <m:mathFont m:val="Cambria Math"/>
   <m:brkBin m:val="before"/>
   <m:brkBinSub m:val="&#45;-"/>
   <m:smallFrac m:val="off"/>
   <m:dispDef/>
   <m:lMargin m:val="0"/>
   <m:rMargin m:val="0"/>
   <m:defJc m:val="centerGroup"/>
   <m:wrapIndent m:val="1440"/>
   <m:intLim m:val="subSup"/>
   <m:naryLim m:val="undOvr"/>
  </m:mathPr></w:WordDocument>
</xml><![endif]--><!--[if gte mso 9]><xml>
 <w:LatentStyles DefLockedState="false" DefUnhideWhenUsed="false"
  DefSemiHidden="false" DefQFormat="false" DefPriority="99"
  LatentStyleCount="380">
  <w:LsdException Locked="false" Priority="0" QFormat="true" Name="Normal"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 1"/>
  <w:LsdException Locked="false" Priority="9" SemiHidden="true"
   UnhideWhenUsed="true" QFormat="true" Name="heading 2"/>
  <w:LsdException Locked="false" Priority="9" SemiHidden="true"
   UnhideWhenUsed="true" QFormat="true" Name="heading 3"/>
  <w:LsdException Locked="false" Priority="9" SemiHidden="true"
   UnhideWhenUsed="true" QFormat="true" Name="heading 4"/>
  <w:LsdException Locked="false" Priority="9" SemiHidden="true"
   UnhideWhenUsed="true" QFormat="true" Name="heading 5"/>
  <w:LsdException Locked="false" Priority="9" SemiHidden="true"
   UnhideWhenUsed="true" QFormat="true" Name="heading 6"/>
  <w:LsdException Locked="false" Priority="9" SemiHidden="true"
   UnhideWhenUsed="true" QFormat="true" Name="heading 7"/>
  <w:LsdException Locked="false" Priority="9" SemiHidden="true"
   UnhideWhenUsed="true" QFormat="true" Name="heading 8"/>
  <w:LsdException Locked="false" Priority="9" SemiHidden="true"
   UnhideWhenUsed="true" QFormat="true" Name="heading 9"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="index 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="index 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="index 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="index 4"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="index 5"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="index 6"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="index 7"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="index 8"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="index 9"/>
  <w:LsdException Locked="false" Priority="39" SemiHidden="true"
   UnhideWhenUsed="true" Name="toc 1"/>
  <w:LsdException Locked="false" Priority="39" SemiHidden="true"
   UnhideWhenUsed="true" Name="toc 2"/>
  <w:LsdException Locked="false" Priority="39" SemiHidden="true"
   UnhideWhenUsed="true" Name="toc 3"/>
  <w:LsdException Locked="false" Priority="39" SemiHidden="true"
   UnhideWhenUsed="true" Name="toc 4"/>
  <w:LsdException Locked="false" Priority="39" SemiHidden="true"
   UnhideWhenUsed="true" Name="toc 5"/>
  <w:LsdException Locked="false" Priority="39" SemiHidden="true"
   UnhideWhenUsed="true" Name="toc 6"/>
  <w:LsdException Locked="false" Priority="39" SemiHidden="true"
   UnhideWhenUsed="true" Name="toc 7"/>
  <w:LsdException Locked="false" Priority="39" SemiHidden="true"
   UnhideWhenUsed="true" Name="toc 8"/>
  <w:LsdException Locked="false" Priority="39" SemiHidden="true"
   UnhideWhenUsed="true" Name="toc 9"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Normal Indent"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="footnote text"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="annotation text"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="header"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="footer"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="index heading"/>
  <w:LsdException Locked="false" Priority="35" SemiHidden="true"
   UnhideWhenUsed="true" QFormat="true" Name="caption"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="table of figures"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="envelope address"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="envelope return"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="footnote reference"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="annotation reference"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="line number"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="page number"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="endnote reference"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="endnote text"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="table of authorities"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="macro"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="toa heading"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Bullet"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Number"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List 4"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List 5"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Bullet 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Bullet 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Bullet 4"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Bullet 5"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Number 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Number 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Number 4"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Number 5"/>
  <w:LsdException Locked="false" Priority="10" QFormat="true" Name="Title"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Closing"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Signature"/>
  <w:LsdException Locked="false" Priority="1" SemiHidden="true"
   UnhideWhenUsed="true" Name="Default Paragraph Font"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Body Text"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Body Text Indent"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Continue"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Continue 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Continue 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Continue 4"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Continue 5"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Message Header"/>
  <w:LsdException Locked="false" Priority="11" QFormat="true" Name="Subtitle"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Salutation"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Date"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Body Text First Indent"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Body Text First Indent 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Note Heading"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Body Text 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Body Text 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Body Text Indent 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Body Text Indent 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Block Text"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Hyperlink"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="FollowedHyperlink"/>
  <w:LsdException Locked="false" Priority="22" QFormat="true" Name="Strong"/>
  <w:LsdException Locked="false" Priority="20" QFormat="true" Name="Emphasis"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Document Map"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Plain Text"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="E-mail Signature"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Top of Form"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Bottom of Form"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Normal (Web)"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Acronym"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Address"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Cite"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Code"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Definition"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Keyboard"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Preformatted"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Sample"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Typewriter"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Variable"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Normal Table"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="annotation subject"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="No List"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Outline List 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Outline List 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Outline List 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Simple 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Simple 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Simple 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Classic 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Classic 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Classic 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Classic 4"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Colorful 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Colorful 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Colorful 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Columns 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Columns 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Columns 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Columns 4"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Columns 5"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Grid 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Grid 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Grid 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Grid 4"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Grid 5"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Grid 6"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Grid 7"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Grid 8"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table List 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table List 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table List 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table List 4"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table List 5"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table List 6"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table List 7"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table List 8"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table 3D effects 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table 3D effects 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table 3D effects 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Contemporary"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Elegant"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Professional"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Subtle 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Subtle 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Web 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Web 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Web 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Balloon Text"/>
  <w:LsdException Locked="false" Priority="39" Name="Table Grid"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Theme"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Note Level 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Note Level 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Note Level 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Note Level 4"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Note Level 5"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Note Level 6"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Note Level 7"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Note Level 8"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Note Level 9"/>
  <w:LsdException Locked="false" SemiHidden="true" Name="Placeholder Text"/>
  <w:LsdException Locked="false" Priority="1" QFormat="true" Name="No Spacing"/>
  <w:LsdException Locked="false" Priority="60" Name="Light Shading"/>
  <w:LsdException Locked="false" Priority="61" Name="Light List"/>
  <w:LsdException Locked="false" Priority="62" Name="Light Grid"/>
  <w:LsdException Locked="false" Priority="63" Name="Medium Shading 1"/>
  <w:LsdException Locked="false" Priority="64" Name="Medium Shading 2"/>
  <w:LsdException Locked="false" Priority="65" Name="Medium List 1"/>
  <w:LsdException Locked="false" Priority="66" Name="Medium List 2"/>
  <w:LsdException Locked="false" Priority="67" Name="Medium Grid 1"/>
  <w:LsdException Locked="false" Priority="68" Name="Medium Grid 2"/>
  <w:LsdException Locked="false" Priority="69" Name="Medium Grid 3"/>
  <w:LsdException Locked="false" Priority="70" Name="Dark List"/>
  <w:LsdException Locked="false" Priority="71" Name="Colorful Shading"/>
  <w:LsdException Locked="false" Priority="72" Name="Colorful List"/>
  <w:LsdException Locked="false" Priority="73" Name="Colorful Grid"/>
  <w:LsdException Locked="false" Priority="60" Name="Light Shading Accent 1"/>
  <w:LsdException Locked="false" Priority="61" Name="Light List Accent 1"/>
  <w:LsdException Locked="false" Priority="62" Name="Light Grid Accent 1"/>
  <w:LsdException Locked="false" Priority="63" Name="Medium Shading 1 Accent 1"/>
  <w:LsdException Locked="false" Priority="64" Name="Medium Shading 2 Accent 1"/>
  <w:LsdException Locked="false" Priority="65" Name="Medium List 1 Accent 1"/>
  <w:LsdException Locked="false" SemiHidden="true" Name="Revision"/>
  <w:LsdException Locked="false" Priority="34" QFormat="true"
   Name="List Paragraph"/>
  <w:LsdException Locked="false" Priority="29" QFormat="true" Name="Quote"/>
  <w:LsdException Locked="false" Priority="30" QFormat="true"
   Name="Intense Quote"/>
  <w:LsdException Locked="false" Priority="66" Name="Medium List 2 Accent 1"/>
  <w:LsdException Locked="false" Priority="67" Name="Medium Grid 1 Accent 1"/>
  <w:LsdException Locked="false" Priority="68" Name="Medium Grid 2 Accent 1"/>
  <w:LsdException Locked="false" Priority="69" Name="Medium Grid 3 Accent 1"/>
  <w:LsdException Locked="false" Priority="70" Name="Dark List Accent 1"/>
  <w:LsdException Locked="false" Priority="71" Name="Colorful Shading Accent 1"/>
  <w:LsdException Locked="false" Priority="72" Name="Colorful List Accent 1"/>
  <w:LsdException Locked="false" Priority="73" Name="Colorful Grid Accent 1"/>
  <w:LsdException Locked="false" Priority="60" Name="Light Shading Accent 2"/>
  <w:LsdException Locked="false" Priority="61" Name="Light List Accent 2"/>
  <w:LsdException Locked="false" Priority="62" Name="Light Grid Accent 2"/>
  <w:LsdException Locked="false" Priority="63" Name="Medium Shading 1 Accent 2"/>
  <w:LsdException Locked="false" Priority="64" Name="Medium Shading 2 Accent 2"/>
  <w:LsdException Locked="false" Priority="65" Name="Medium List 1 Accent 2"/>
  <w:LsdException Locked="false" Priority="66" Name="Medium List 2 Accent 2"/>
  <w:LsdException Locked="false" Priority="67" Name="Medium Grid 1 Accent 2"/>
  <w:LsdException Locked="false" Priority="68" Name="Medium Grid 2 Accent 2"/>
  <w:LsdException Locked="false" Priority="69" Name="Medium Grid 3 Accent 2"/>
  <w:LsdException Locked="false" Priority="70" Name="Dark List Accent 2"/>
  <w:LsdException Locked="false" Priority="71" Name="Colorful Shading Accent 2"/>
  <w:LsdException Locked="false" Priority="72" Name="Colorful List Accent 2"/>
  <w:LsdException Locked="false" Priority="73" Name="Colorful Grid Accent 2"/>
  <w:LsdException Locked="false" Priority="60" Name="Light Shading Accent 3"/>
  <w:LsdException Locked="false" Priority="61" Name="Light List Accent 3"/>
  <w:LsdException Locked="false" Priority="62" Name="Light Grid Accent 3"/>
  <w:LsdException Locked="false" Priority="63" Name="Medium Shading 1 Accent 3"/>
  <w:LsdException Locked="false" Priority="64" Name="Medium Shading 2 Accent 3"/>
  <w:LsdException Locked="false" Priority="65" Name="Medium List 1 Accent 3"/>
  <w:LsdException Locked="false" Priority="66" Name="Medium List 2 Accent 3"/>
  <w:LsdException Locked="false" Priority="67" Name="Medium Grid 1 Accent 3"/>
  <w:LsdException Locked="false" Priority="68" Name="Medium Grid 2 Accent 3"/>
  <w:LsdException Locked="false" Priority="69" Name="Medium Grid 3 Accent 3"/>
  <w:LsdException Locked="false" Priority="70" Name="Dark List Accent 3"/>
  <w:LsdException Locked="false" Priority="71" Name="Colorful Shading Accent 3"/>
  <w:LsdException Locked="false" Priority="72" Name="Colorful List Accent 3"/>
  <w:LsdException Locked="false" Priority="73" Name="Colorful Grid Accent 3"/>
  <w:LsdException Locked="false" Priority="60" Name="Light Shading Accent 4"/>
  <w:LsdException Locked="false" Priority="61" Name="Light List Accent 4"/>
  <w:LsdException Locked="false" Priority="62" Name="Light Grid Accent 4"/>
  <w:LsdException Locked="false" Priority="63" Name="Medium Shading 1 Accent 4"/>
  <w:LsdException Locked="false" Priority="64" Name="Medium Shading 2 Accent 4"/>
  <w:LsdException Locked="false" Priority="65" Name="Medium List 1 Accent 4"/>
  <w:LsdException Locked="false" Priority="66" Name="Medium List 2 Accent 4"/>
  <w:LsdException Locked="false" Priority="67" Name="Medium Grid 1 Accent 4"/>
  <w:LsdException Locked="false" Priority="68" Name="Medium Grid 2 Accent 4"/>
  <w:LsdException Locked="false" Priority="69" Name="Medium Grid 3 Accent 4"/>
  <w:LsdException Locked="false" Priority="70" Name="Dark List Accent 4"/>
  <w:LsdException Locked="false" Priority="71" Name="Colorful Shading Accent 4"/>
  <w:LsdException Locked="false" Priority="72" Name="Colorful List Accent 4"/>
  <w:LsdException Locked="false" Priority="73" Name="Colorful Grid Accent 4"/>
  <w:LsdException Locked="false" Priority="60" Name="Light Shading Accent 5"/>
  <w:LsdException Locked="false" Priority="61" Name="Light List Accent 5"/>
  <w:LsdException Locked="false" Priority="62" Name="Light Grid Accent 5"/>
  <w:LsdException Locked="false" Priority="63" Name="Medium Shading 1 Accent 5"/>
  <w:LsdException Locked="false" Priority="64" Name="Medium Shading 2 Accent 5"/>
  <w:LsdException Locked="false" Priority="65" Name="Medium List 1 Accent 5"/>
  <w:LsdException Locked="false" Priority="66" Name="Medium List 2 Accent 5"/>
  <w:LsdException Locked="false" Priority="67" Name="Medium Grid 1 Accent 5"/>
  <w:LsdException Locked="false" Priority="68" Name="Medium Grid 2 Accent 5"/>
  <w:LsdException Locked="false" Priority="69" Name="Medium Grid 3 Accent 5"/>
  <w:LsdException Locked="false" Priority="70" Name="Dark List Accent 5"/>
  <w:LsdException Locked="false" Priority="71" Name="Colorful Shading Accent 5"/>
  <w:LsdException Locked="false" Priority="72" Name="Colorful List Accent 5"/>
  <w:LsdException Locked="false" Priority="73" Name="Colorful Grid Accent 5"/>
  <w:LsdException Locked="false" Priority="60" Name="Light Shading Accent 6"/>
  <w:LsdException Locked="false" Priority="61" Name="Light List Accent 6"/>
  <w:LsdException Locked="false" Priority="62" Name="Light Grid Accent 6"/>
  <w:LsdException Locked="false" Priority="63" Name="Medium Shading 1 Accent 6"/>
  <w:LsdException Locked="false" Priority="64" Name="Medium Shading 2 Accent 6"/>
  <w:LsdException Locked="false" Priority="65" Name="Medium List 1 Accent 6"/>
  <w:LsdException Locked="false" Priority="66" Name="Medium List 2 Accent 6"/>
  <w:LsdException Locked="false" Priority="67" Name="Medium Grid 1 Accent 6"/>
  <w:LsdException Locked="false" Priority="68" Name="Medium Grid 2 Accent 6"/>
  <w:LsdException Locked="false" Priority="69" Name="Medium Grid 3 Accent 6"/>
  <w:LsdException Locked="false" Priority="70" Name="Dark List Accent 6"/>
  <w:LsdException Locked="false" Priority="71" Name="Colorful Shading Accent 6"/>
  <w:LsdException Locked="false" Priority="72" Name="Colorful List Accent 6"/>
  <w:LsdException Locked="false" Priority="73" Name="Colorful Grid Accent 6"/>
  <w:LsdException Locked="false" Priority="19" QFormat="true"
   Name="Subtle Emphasis"/>
  <w:LsdException Locked="false" Priority="21" QFormat="true"
   Name="Intense Emphasis"/>
  <w:LsdException Locked="false" Priority="31" QFormat="true"
   Name="Subtle Reference"/>
  <w:LsdException Locked="false" Priority="32" QFormat="true"
   Name="Intense Reference"/>
  <w:LsdException Locked="false" Priority="33" QFormat="true" Name="Book Title"/>
  <w:LsdException Locked="false" Priority="37" SemiHidden="true"
   UnhideWhenUsed="true" Name="Bibliography"/>
  <w:LsdException Locked="false" Priority="39" SemiHidden="true"
   UnhideWhenUsed="true" QFormat="true" Name="TOC Heading"/>
  <w:LsdException Locked="false" Priority="41" Name="Plain Table 1"/>
  <w:LsdException Locked="false" Priority="42" Name="Plain Table 2"/>
  <w:LsdException Locked="false" Priority="43" Name="Plain Table 3"/>
  <w:LsdException Locked="false" Priority="44" Name="Plain Table 4"/>
  <w:LsdException Locked="false" Priority="45" Name="Plain Table 5"/>
  <w:LsdException Locked="false" Priority="40" Name="Grid Table Light"/>
  <w:LsdException Locked="false" Priority="46" Name="Grid Table 1 Light"/>
  <w:LsdException Locked="false" Priority="47" Name="Grid Table 2"/>
  <w:LsdException Locked="false" Priority="48" Name="Grid Table 3"/>
  <w:LsdException Locked="false" Priority="49" Name="Grid Table 4"/>
  <w:LsdException Locked="false" Priority="50" Name="Grid Table 5 Dark"/>
  <w:LsdException Locked="false" Priority="51" Name="Grid Table 6 Colorful"/>
  <w:LsdException Locked="false" Priority="52" Name="Grid Table 7 Colorful"/>
  <w:LsdException Locked="false" Priority="46"
   Name="Grid Table 1 Light Accent 1"/>
  <w:LsdException Locked="false" Priority="47" Name="Grid Table 2 Accent 1"/>
  <w:LsdException Locked="false" Priority="48" Name="Grid Table 3 Accent 1"/>
  <w:LsdException Locked="false" Priority="49" Name="Grid Table 4 Accent 1"/>
  <w:LsdException Locked="false" Priority="50" Name="Grid Table 5 Dark Accent 1"/>
  <w:LsdException Locked="false" Priority="51"
   Name="Grid Table 6 Colorful Accent 1"/>
  <w:LsdException Locked="false" Priority="52"
   Name="Grid Table 7 Colorful Accent 1"/>
  <w:LsdException Locked="false" Priority="46"
   Name="Grid Table 1 Light Accent 2"/>
  <w:LsdException Locked="false" Priority="47" Name="Grid Table 2 Accent 2"/>
  <w:LsdException Locked="false" Priority="48" Name="Grid Table 3 Accent 2"/>
  <w:LsdException Locked="false" Priority="49" Name="Grid Table 4 Accent 2"/>
  <w:LsdException Locked="false" Priority="50" Name="Grid Table 5 Dark Accent 2"/>
  <w:LsdException Locked="false" Priority="51"
   Name="Grid Table 6 Colorful Accent 2"/>
  <w:LsdException Locked="false" Priority="52"
   Name="Grid Table 7 Colorful Accent 2"/>
  <w:LsdException Locked="false" Priority="46"
   Name="Grid Table 1 Light Accent 3"/>
  <w:LsdException Locked="false" Priority="47" Name="Grid Table 2 Accent 3"/>
  <w:LsdException Locked="false" Priority="48" Name="Grid Table 3 Accent 3"/>
  <w:LsdException Locked="false" Priority="49" Name="Grid Table 4 Accent 3"/>
  <w:LsdException Locked="false" Priority="50" Name="Grid Table 5 Dark Accent 3"/>
  <w:LsdException Locked="false" Priority="51"
   Name="Grid Table 6 Colorful Accent 3"/>
  <w:LsdException Locked="false" Priority="52"
   Name="Grid Table 7 Colorful Accent 3"/>
  <w:LsdException Locked="false" Priority="46"
   Name="Grid Table 1 Light Accent 4"/>
  <w:LsdException Locked="false" Priority="47" Name="Grid Table 2 Accent 4"/>
  <w:LsdException Locked="false" Priority="48" Name="Grid Table 3 Accent 4"/>
  <w:LsdException Locked="false" Priority="49" Name="Grid Table 4 Accent 4"/>
  <w:LsdException Locked="false" Priority="50" Name="Grid Table 5 Dark Accent 4"/>
  <w:LsdException Locked="false" Priority="51"
   Name="Grid Table 6 Colorful Accent 4"/>
  <w:LsdException Locked="false" Priority="52"
   Name="Grid Table 7 Colorful Accent 4"/>
  <w:LsdException Locked="false" Priority="46"
   Name="Grid Table 1 Light Accent 5"/>
  <w:LsdException Locked="false" Priority="47" Name="Grid Table 2 Accent 5"/>
  <w:LsdException Locked="false" Priority="48" Name="Grid Table 3 Accent 5"/>
  <w:LsdException Locked="false" Priority="49" Name="Grid Table 4 Accent 5"/>
  <w:LsdException Locked="false" Priority="50" Name="Grid Table 5 Dark Accent 5"/>
  <w:LsdException Locked="false" Priority="51"
   Name="Grid Table 6 Colorful Accent 5"/>
  <w:LsdException Locked="false" Priority="52"
   Name="Grid Table 7 Colorful Accent 5"/>
  <w:LsdException Locked="false" Priority="46"
   Name="Grid Table 1 Light Accent 6"/>
  <w:LsdException Locked="false" Priority="47" Name="Grid Table 2 Accent 6"/>
  <w:LsdException Locked="false" Priority="48" Name="Grid Table 3 Accent 6"/>
  <w:LsdException Locked="false" Priority="49" Name="Grid Table 4 Accent 6"/>
  <w:LsdException Locked="false" Priority="50" Name="Grid Table 5 Dark Accent 6"/>
  <w:LsdException Locked="false" Priority="51"
   Name="Grid Table 6 Colorful Accent 6"/>
  <w:LsdException Locked="false" Priority="52"
   Name="Grid Table 7 Colorful Accent 6"/>
  <w:LsdException Locked="false" Priority="46" Name="List Table 1 Light"/>
  <w:LsdException Locked="false" Priority="47" Name="List Table 2"/>
  <w:LsdException Locked="false" Priority="48" Name="List Table 3"/>
  <w:LsdException Locked="false" Priority="49" Name="List Table 4"/>
  <w:LsdException Locked="false" Priority="50" Name="List Table 5 Dark"/>
  <w:LsdException Locked="false" Priority="51" Name="List Table 6 Colorful"/>
  <w:LsdException Locked="false" Priority="52" Name="List Table 7 Colorful"/>
  <w:LsdException Locked="false" Priority="46"
   Name="List Table 1 Light Accent 1"/>
  <w:LsdException Locked="false" Priority="47" Name="List Table 2 Accent 1"/>
  <w:LsdException Locked="false" Priority="48" Name="List Table 3 Accent 1"/>
  <w:LsdException Locked="false" Priority="49" Name="List Table 4 Accent 1"/>
  <w:LsdException Locked="false" Priority="50" Name="List Table 5 Dark Accent 1"/>
  <w:LsdException Locked="false" Priority="51"
   Name="List Table 6 Colorful Accent 1"/>
  <w:LsdException Locked="false" Priority="52"
   Name="List Table 7 Colorful Accent 1"/>
  <w:LsdException Locked="false" Priority="46"
   Name="List Table 1 Light Accent 2"/>
  <w:LsdException Locked="false" Priority="47" Name="List Table 2 Accent 2"/>
  <w:LsdException Locked="false" Priority="48" Name="List Table 3 Accent 2"/>
  <w:LsdException Locked="false" Priority="49" Name="List Table 4 Accent 2"/>
  <w:LsdException Locked="false" Priority="50" Name="List Table 5 Dark Accent 2"/>
  <w:LsdException Locked="false" Priority="51"
   Name="List Table 6 Colorful Accent 2"/>
  <w:LsdException Locked="false" Priority="52"
   Name="List Table 7 Colorful Accent 2"/>
  <w:LsdException Locked="false" Priority="46"
   Name="List Table 1 Light Accent 3"/>
  <w:LsdException Locked="false" Priority="47" Name="List Table 2 Accent 3"/>
  <w:LsdException Locked="false" Priority="48" Name="List Table 3 Accent 3"/>
  <w:LsdException Locked="false" Priority="49" Name="List Table 4 Accent 3"/>
  <w:LsdException Locked="false" Priority="50" Name="List Table 5 Dark Accent 3"/>
  <w:LsdException Locked="false" Priority="51"
   Name="List Table 6 Colorful Accent 3"/>
  <w:LsdException Locked="false" Priority="52"
   Name="List Table 7 Colorful Accent 3"/>
  <w:LsdException Locked="false" Priority="46"
   Name="List Table 1 Light Accent 4"/>
  <w:LsdException Locked="false" Priority="47" Name="List Table 2 Accent 4"/>
  <w:LsdException Locked="false" Priority="48" Name="List Table 3 Accent 4"/>
  <w:LsdException Locked="false" Priority="49" Name="List Table 4 Accent 4"/>
  <w:LsdException Locked="false" Priority="50" Name="List Table 5 Dark Accent 4"/>
  <w:LsdException Locked="false" Priority="51"
   Name="List Table 6 Colorful Accent 4"/>
  <w:LsdException Locked="false" Priority="52"
   Name="List Table 7 Colorful Accent 4"/>
  <w:LsdException Locked="false" Priority="46"
   Name="List Table 1 Light Accent 5"/>
  <w:LsdException Locked="false" Priority="47" Name="List Table 2 Accent 5"/>
  <w:LsdException Locked="false" Priority="48" Name="List Table 3 Accent 5"/>
  <w:LsdException Locked="false" Priority="49" Name="List Table 4 Accent 5"/>
  <w:LsdException Locked="false" Priority="50" Name="List Table 5 Dark Accent 5"/>
  <w:LsdException Locked="false" Priority="51"
   Name="List Table 6 Colorful Accent 5"/>
  <w:LsdException Locked="false" Priority="52"
   Name="List Table 7 Colorful Accent 5"/>
  <w:LsdException Locked="false" Priority="46"
   Name="List Table 1 Light Accent 6"/>
  <w:LsdException Locked="false" Priority="47" Name="List Table 2 Accent 6"/>
  <w:LsdException Locked="false" Priority="48" Name="List Table 3 Accent 6"/>
  <w:LsdException Locked="false" Priority="49" Name="List Table 4 Accent 6"/>
  <w:LsdException Locked="false" Priority="50" Name="List Table 5 Dark Accent 6"/>
  <w:LsdException Locked="false" Priority="51"
   Name="List Table 6 Colorful Accent 6"/>
  <w:LsdException Locked="false" Priority="52"
   Name="List Table 7 Colorful Accent 6"/>
 </w:LatentStyles>
</xml><![endif]--> <!--[if gte mso 10]>
<style>
 /* Style Definitions */
table.MsoNormalTable
	{mso-style-name:"Table Normal";
	mso-tstyle-rowband-size:0;
	mso-tstyle-colband-size:0;
	mso-style-noshow:yes;
	mso-style-priority:99;
	mso-style-parent:"";
	mso-padding-alt:0in 5.4pt 0in 5.4pt;
	mso-para-margin-top:0in;
	mso-para-margin-right:0in;
	mso-para-margin-bottom:10.0pt;
	mso-para-margin-left:0in;
	line-height:115%;
	mso-pagination:widow-orphan;
	font-size:11.0pt;
	font-family:Calibri;
	color:black;}
</style>
<![endif]--> <!--StartFragment--><strong><span style="font-size: 11.0pt; line-height: 115%; font-family: Calibri; mso-fareast-font-family: Calibri; mso-bidi-font-family: Calibri; mso-ansi-language: EN-US; mso-fareast-language: EN-US; mso-bidi-language: AR-SA;">The Playlist topic is aligned with the intent of the Common Core State Standards, other nationally recognized content standards (including educator learning standards), or other state specific standards.</span></strong><!--EndFragment--></p>',
    'format' => 'full_html',
  );
  $export['qc_78306_criteria_1_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_78306_criteria_2_description';
  $strongarm->value = array(
    'value' => '<p><span style="line-height: 16px;">a. The Organization of Playlist section of the Educator Learning Guide includes information on how the resources build off of each other or progress from one topic to the next.</span></p><p><span style="line-height: 16px;">b. The Specific Connection to the Formative Assessment Process section of the Cover Profile Guide includes information on how the formative assessment process aligns with the organization or progression of the Playlist</span></p>',
    'format' => 'full_html',
  );
  $export['qc_78306_criteria_2_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_78306_criteria_2_desc_state';
  $strongarm->value = 'collapsed';
  $export['qc_78306_criteria_2_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_78306_criteria_2_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_78306_criteria_2_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_78306_criteria_2_title';
  $strongarm->value = array(
    'value' => '<p>&nbsp;</p><!--[if gte mso 9]><xml>
 <w:WordDocument>
  <w:View>Normal</w:View>
  <w:Zoom>0</w:Zoom>
  <w:TrackMoves/>
  <w:TrackFormatting/>
  <w:PunctuationKerning/>
  <w:ValidateAgainstSchemas/>
  <w:SaveIfXMLInvalid>false</w:SaveIfXMLInvalid>
  <w:IgnoreMixedContent>false</w:IgnoreMixedContent>
  <w:AlwaysShowPlaceholderText>false</w:AlwaysShowPlaceholderText>
  <w:DoNotPromoteQF/>
  <w:LidThemeOther>EN-US</w:LidThemeOther>
  <w:LidThemeAsian>X-NONE</w:LidThemeAsian>
  <w:LidThemeComplexScript>X-NONE</w:LidThemeComplexScript>
  <w:Compatibility>
   <w:BreakWrappedTables/>
   <w:SnapToGridInCell/>
   <w:WrapTextWithPunct/>
   <w:UseAsianBreakRules/>
   <w:DontGrowAutofit/>
   <w:SplitPgBreakAndParaMark/>
   <w:EnableOpenTypeKerning/>
   <w:DontFlipMirrorIndents/>
   <w:OverrideTableStyleHps/>
  </w:Compatibility>
  <m:mathPr>
   <m:mathFont m:val="Cambria Math"/>
   <m:brkBin m:val="before"/>
   <m:brkBinSub m:val="&#45;-"/>
   <m:smallFrac m:val="off"/>
   <m:dispDef/>
   <m:lMargin m:val="0"/>
   <m:rMargin m:val="0"/>
   <m:defJc m:val="centerGroup"/>
   <m:wrapIndent m:val="1440"/>
   <m:intLim m:val="subSup"/>
   <m:naryLim m:val="undOvr"/>
  </m:mathPr></w:WordDocument>
</xml><![endif]--><!--[if gte mso 9]><xml>
 <w:LatentStyles DefLockedState="false" DefUnhideWhenUsed="false"
  DefSemiHidden="false" DefQFormat="false" DefPriority="99"
  LatentStyleCount="380">
  <w:LsdException Locked="false" Priority="0" QFormat="true" Name="Normal"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 1"/>
  <w:LsdException Locked="false" Priority="9" SemiHidden="true"
   UnhideWhenUsed="true" QFormat="true" Name="heading 2"/>
  <w:LsdException Locked="false" Priority="9" SemiHidden="true"
   UnhideWhenUsed="true" QFormat="true" Name="heading 3"/>
  <w:LsdException Locked="false" Priority="9" SemiHidden="true"
   UnhideWhenUsed="true" QFormat="true" Name="heading 4"/>
  <w:LsdException Locked="false" Priority="9" SemiHidden="true"
   UnhideWhenUsed="true" QFormat="true" Name="heading 5"/>
  <w:LsdException Locked="false" Priority="9" SemiHidden="true"
   UnhideWhenUsed="true" QFormat="true" Name="heading 6"/>
  <w:LsdException Locked="false" Priority="9" SemiHidden="true"
   UnhideWhenUsed="true" QFormat="true" Name="heading 7"/>
  <w:LsdException Locked="false" Priority="9" SemiHidden="true"
   UnhideWhenUsed="true" QFormat="true" Name="heading 8"/>
  <w:LsdException Locked="false" Priority="9" SemiHidden="true"
   UnhideWhenUsed="true" QFormat="true" Name="heading 9"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="index 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="index 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="index 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="index 4"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="index 5"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="index 6"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="index 7"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="index 8"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="index 9"/>
  <w:LsdException Locked="false" Priority="39" SemiHidden="true"
   UnhideWhenUsed="true" Name="toc 1"/>
  <w:LsdException Locked="false" Priority="39" SemiHidden="true"
   UnhideWhenUsed="true" Name="toc 2"/>
  <w:LsdException Locked="false" Priority="39" SemiHidden="true"
   UnhideWhenUsed="true" Name="toc 3"/>
  <w:LsdException Locked="false" Priority="39" SemiHidden="true"
   UnhideWhenUsed="true" Name="toc 4"/>
  <w:LsdException Locked="false" Priority="39" SemiHidden="true"
   UnhideWhenUsed="true" Name="toc 5"/>
  <w:LsdException Locked="false" Priority="39" SemiHidden="true"
   UnhideWhenUsed="true" Name="toc 6"/>
  <w:LsdException Locked="false" Priority="39" SemiHidden="true"
   UnhideWhenUsed="true" Name="toc 7"/>
  <w:LsdException Locked="false" Priority="39" SemiHidden="true"
   UnhideWhenUsed="true" Name="toc 8"/>
  <w:LsdException Locked="false" Priority="39" SemiHidden="true"
   UnhideWhenUsed="true" Name="toc 9"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Normal Indent"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="footnote text"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="annotation text"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="header"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="footer"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="index heading"/>
  <w:LsdException Locked="false" Priority="35" SemiHidden="true"
   UnhideWhenUsed="true" QFormat="true" Name="caption"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="table of figures"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="envelope address"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="envelope return"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="footnote reference"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="annotation reference"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="line number"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="page number"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="endnote reference"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="endnote text"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="table of authorities"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="macro"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="toa heading"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Bullet"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Number"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List 4"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List 5"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Bullet 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Bullet 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Bullet 4"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Bullet 5"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Number 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Number 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Number 4"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Number 5"/>
  <w:LsdException Locked="false" Priority="10" QFormat="true" Name="Title"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Closing"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Signature"/>
  <w:LsdException Locked="false" Priority="1" SemiHidden="true"
   UnhideWhenUsed="true" Name="Default Paragraph Font"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Body Text"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Body Text Indent"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Continue"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Continue 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Continue 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Continue 4"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="List Continue 5"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Message Header"/>
  <w:LsdException Locked="false" Priority="11" QFormat="true" Name="Subtitle"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Salutation"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Date"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Body Text First Indent"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Body Text First Indent 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Note Heading"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Body Text 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Body Text 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Body Text Indent 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Body Text Indent 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Block Text"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Hyperlink"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="FollowedHyperlink"/>
  <w:LsdException Locked="false" Priority="22" QFormat="true" Name="Strong"/>
  <w:LsdException Locked="false" Priority="20" QFormat="true" Name="Emphasis"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Document Map"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Plain Text"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="E-mail Signature"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Top of Form"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Bottom of Form"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Normal (Web)"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Acronym"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Address"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Cite"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Code"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Definition"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Keyboard"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Preformatted"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Sample"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Typewriter"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="HTML Variable"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Normal Table"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="annotation subject"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="No List"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Outline List 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Outline List 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Outline List 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Simple 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Simple 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Simple 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Classic 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Classic 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Classic 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Classic 4"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Colorful 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Colorful 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Colorful 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Columns 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Columns 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Columns 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Columns 4"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Columns 5"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Grid 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Grid 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Grid 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Grid 4"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Grid 5"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Grid 6"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Grid 7"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Grid 8"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table List 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table List 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table List 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table List 4"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table List 5"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table List 6"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table List 7"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table List 8"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table 3D effects 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table 3D effects 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table 3D effects 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Contemporary"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Elegant"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Professional"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Subtle 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Subtle 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Web 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Web 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Web 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Balloon Text"/>
  <w:LsdException Locked="false" Priority="39" Name="Table Grid"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Table Theme"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Note Level 1"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Note Level 2"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Note Level 3"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Note Level 4"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Note Level 5"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Note Level 6"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Note Level 7"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Note Level 8"/>
  <w:LsdException Locked="false" SemiHidden="true" UnhideWhenUsed="true"
   Name="Note Level 9"/>
  <w:LsdException Locked="false" SemiHidden="true" Name="Placeholder Text"/>
  <w:LsdException Locked="false" Priority="1" QFormat="true" Name="No Spacing"/>
  <w:LsdException Locked="false" Priority="60" Name="Light Shading"/>
  <w:LsdException Locked="false" Priority="61" Name="Light List"/>
  <w:LsdException Locked="false" Priority="62" Name="Light Grid"/>
  <w:LsdException Locked="false" Priority="63" Name="Medium Shading 1"/>
  <w:LsdException Locked="false" Priority="64" Name="Medium Shading 2"/>
  <w:LsdException Locked="false" Priority="65" Name="Medium List 1"/>
  <w:LsdException Locked="false" Priority="66" Name="Medium List 2"/>
  <w:LsdException Locked="false" Priority="67" Name="Medium Grid 1"/>
  <w:LsdException Locked="false" Priority="68" Name="Medium Grid 2"/>
  <w:LsdException Locked="false" Priority="69" Name="Medium Grid 3"/>
  <w:LsdException Locked="false" Priority="70" Name="Dark List"/>
  <w:LsdException Locked="false" Priority="71" Name="Colorful Shading"/>
  <w:LsdException Locked="false" Priority="72" Name="Colorful List"/>
  <w:LsdException Locked="false" Priority="73" Name="Colorful Grid"/>
  <w:LsdException Locked="false" Priority="60" Name="Light Shading Accent 1"/>
  <w:LsdException Locked="false" Priority="61" Name="Light List Accent 1"/>
  <w:LsdException Locked="false" Priority="62" Name="Light Grid Accent 1"/>
  <w:LsdException Locked="false" Priority="63" Name="Medium Shading 1 Accent 1"/>
  <w:LsdException Locked="false" Priority="64" Name="Medium Shading 2 Accent 1"/>
  <w:LsdException Locked="false" Priority="65" Name="Medium List 1 Accent 1"/>
  <w:LsdException Locked="false" SemiHidden="true" Name="Revision"/>
  <w:LsdException Locked="false" Priority="34" QFormat="true"
   Name="List Paragraph"/>
  <w:LsdException Locked="false" Priority="29" QFormat="true" Name="Quote"/>
  <w:LsdException Locked="false" Priority="30" QFormat="true"
   Name="Intense Quote"/>
  <w:LsdException Locked="false" Priority="66" Name="Medium List 2 Accent 1"/>
  <w:LsdException Locked="false" Priority="67" Name="Medium Grid 1 Accent 1"/>
  <w:LsdException Locked="false" Priority="68" Name="Medium Grid 2 Accent 1"/>
  <w:LsdException Locked="false" Priority="69" Name="Medium Grid 3 Accent 1"/>
  <w:LsdException Locked="false" Priority="70" Name="Dark List Accent 1"/>
  <w:LsdException Locked="false" Priority="71" Name="Colorful Shading Accent 1"/>
  <w:LsdException Locked="false" Priority="72" Name="Colorful List Accent 1"/>
  <w:LsdException Locked="false" Priority="73" Name="Colorful Grid Accent 1"/>
  <w:LsdException Locked="false" Priority="60" Name="Light Shading Accent 2"/>
  <w:LsdException Locked="false" Priority="61" Name="Light List Accent 2"/>
  <w:LsdException Locked="false" Priority="62" Name="Light Grid Accent 2"/>
  <w:LsdException Locked="false" Priority="63" Name="Medium Shading 1 Accent 2"/>
  <w:LsdException Locked="false" Priority="64" Name="Medium Shading 2 Accent 2"/>
  <w:LsdException Locked="false" Priority="65" Name="Medium List 1 Accent 2"/>
  <w:LsdException Locked="false" Priority="66" Name="Medium List 2 Accent 2"/>
  <w:LsdException Locked="false" Priority="67" Name="Medium Grid 1 Accent 2"/>
  <w:LsdException Locked="false" Priority="68" Name="Medium Grid 2 Accent 2"/>
  <w:LsdException Locked="false" Priority="69" Name="Medium Grid 3 Accent 2"/>
  <w:LsdException Locked="false" Priority="70" Name="Dark List Accent 2"/>
  <w:LsdException Locked="false" Priority="71" Name="Colorful Shading Accent 2"/>
  <w:LsdException Locked="false" Priority="72" Name="Colorful List Accent 2"/>
  <w:LsdException Locked="false" Priority="73" Name="Colorful Grid Accent 2"/>
  <w:LsdException Locked="false" Priority="60" Name="Light Shading Accent 3"/>
  <w:LsdException Locked="false" Priority="61" Name="Light List Accent 3"/>
  <w:LsdException Locked="false" Priority="62" Name="Light Grid Accent 3"/>
  <w:LsdException Locked="false" Priority="63" Name="Medium Shading 1 Accent 3"/>
  <w:LsdException Locked="false" Priority="64" Name="Medium Shading 2 Accent 3"/>
  <w:LsdException Locked="false" Priority="65" Name="Medium List 1 Accent 3"/>
  <w:LsdException Locked="false" Priority="66" Name="Medium List 2 Accent 3"/>
  <w:LsdException Locked="false" Priority="67" Name="Medium Grid 1 Accent 3"/>
  <w:LsdException Locked="false" Priority="68" Name="Medium Grid 2 Accent 3"/>
  <w:LsdException Locked="false" Priority="69" Name="Medium Grid 3 Accent 3"/>
  <w:LsdException Locked="false" Priority="70" Name="Dark List Accent 3"/>
  <w:LsdException Locked="false" Priority="71" Name="Colorful Shading Accent 3"/>
  <w:LsdException Locked="false" Priority="72" Name="Colorful List Accent 3"/>
  <w:LsdException Locked="false" Priority="73" Name="Colorful Grid Accent 3"/>
  <w:LsdException Locked="false" Priority="60" Name="Light Shading Accent 4"/>
  <w:LsdException Locked="false" Priority="61" Name="Light List Accent 4"/>
  <w:LsdException Locked="false" Priority="62" Name="Light Grid Accent 4"/>
  <w:LsdException Locked="false" Priority="63" Name="Medium Shading 1 Accent 4"/>
  <w:LsdException Locked="false" Priority="64" Name="Medium Shading 2 Accent 4"/>
  <w:LsdException Locked="false" Priority="65" Name="Medium List 1 Accent 4"/>
  <w:LsdException Locked="false" Priority="66" Name="Medium List 2 Accent 4"/>
  <w:LsdException Locked="false" Priority="67" Name="Medium Grid 1 Accent 4"/>
  <w:LsdException Locked="false" Priority="68" Name="Medium Grid 2 Accent 4"/>
  <w:LsdException Locked="false" Priority="69" Name="Medium Grid 3 Accent 4"/>
  <w:LsdException Locked="false" Priority="70" Name="Dark List Accent 4"/>
  <w:LsdException Locked="false" Priority="71" Name="Colorful Shading Accent 4"/>
  <w:LsdException Locked="false" Priority="72" Name="Colorful List Accent 4"/>
  <w:LsdException Locked="false" Priority="73" Name="Colorful Grid Accent 4"/>
  <w:LsdException Locked="false" Priority="60" Name="Light Shading Accent 5"/>
  <w:LsdException Locked="false" Priority="61" Name="Light List Accent 5"/>
  <w:LsdException Locked="false" Priority="62" Name="Light Grid Accent 5"/>
  <w:LsdException Locked="false" Priority="63" Name="Medium Shading 1 Accent 5"/>
  <w:LsdException Locked="false" Priority="64" Name="Medium Shading 2 Accent 5"/>
  <w:LsdException Locked="false" Priority="65" Name="Medium List 1 Accent 5"/>
  <w:LsdException Locked="false" Priority="66" Name="Medium List 2 Accent 5"/>
  <w:LsdException Locked="false" Priority="67" Name="Medium Grid 1 Accent 5"/>
  <w:LsdException Locked="false" Priority="68" Name="Medium Grid 2 Accent 5"/>
  <w:LsdException Locked="false" Priority="69" Name="Medium Grid 3 Accent 5"/>
  <w:LsdException Locked="false" Priority="70" Name="Dark List Accent 5"/>
  <w:LsdException Locked="false" Priority="71" Name="Colorful Shading Accent 5"/>
  <w:LsdException Locked="false" Priority="72" Name="Colorful List Accent 5"/>
  <w:LsdException Locked="false" Priority="73" Name="Colorful Grid Accent 5"/>
  <w:LsdException Locked="false" Priority="60" Name="Light Shading Accent 6"/>
  <w:LsdException Locked="false" Priority="61" Name="Light List Accent 6"/>
  <w:LsdException Locked="false" Priority="62" Name="Light Grid Accent 6"/>
  <w:LsdException Locked="false" Priority="63" Name="Medium Shading 1 Accent 6"/>
  <w:LsdException Locked="false" Priority="64" Name="Medium Shading 2 Accent 6"/>
  <w:LsdException Locked="false" Priority="65" Name="Medium List 1 Accent 6"/>
  <w:LsdException Locked="false" Priority="66" Name="Medium List 2 Accent 6"/>
  <w:LsdException Locked="false" Priority="67" Name="Medium Grid 1 Accent 6"/>
  <w:LsdException Locked="false" Priority="68" Name="Medium Grid 2 Accent 6"/>
  <w:LsdException Locked="false" Priority="69" Name="Medium Grid 3 Accent 6"/>
  <w:LsdException Locked="false" Priority="70" Name="Dark List Accent 6"/>
  <w:LsdException Locked="false" Priority="71" Name="Colorful Shading Accent 6"/>
  <w:LsdException Locked="false" Priority="72" Name="Colorful List Accent 6"/>
  <w:LsdException Locked="false" Priority="73" Name="Colorful Grid Accent 6"/>
  <w:LsdException Locked="false" Priority="19" QFormat="true"
   Name="Subtle Emphasis"/>
  <w:LsdException Locked="false" Priority="21" QFormat="true"
   Name="Intense Emphasis"/>
  <w:LsdException Locked="false" Priority="31" QFormat="true"
   Name="Subtle Reference"/>
  <w:LsdException Locked="false" Priority="32" QFormat="true"
   Name="Intense Reference"/>
  <w:LsdException Locked="false" Priority="33" QFormat="true" Name="Book Title"/>
  <w:LsdException Locked="false" Priority="37" SemiHidden="true"
   UnhideWhenUsed="true" Name="Bibliography"/>
  <w:LsdException Locked="false" Priority="39" SemiHidden="true"
   UnhideWhenUsed="true" QFormat="true" Name="TOC Heading"/>
  <w:LsdException Locked="false" Priority="41" Name="Plain Table 1"/>
  <w:LsdException Locked="false" Priority="42" Name="Plain Table 2"/>
  <w:LsdException Locked="false" Priority="43" Name="Plain Table 3"/>
  <w:LsdException Locked="false" Priority="44" Name="Plain Table 4"/>
  <w:LsdException Locked="false" Priority="45" Name="Plain Table 5"/>
  <w:LsdException Locked="false" Priority="40" Name="Grid Table Light"/>
  <w:LsdException Locked="false" Priority="46" Name="Grid Table 1 Light"/>
  <w:LsdException Locked="false" Priority="47" Name="Grid Table 2"/>
  <w:LsdException Locked="false" Priority="48" Name="Grid Table 3"/>
  <w:LsdException Locked="false" Priority="49" Name="Grid Table 4"/>
  <w:LsdException Locked="false" Priority="50" Name="Grid Table 5 Dark"/>
  <w:LsdException Locked="false" Priority="51" Name="Grid Table 6 Colorful"/>
  <w:LsdException Locked="false" Priority="52" Name="Grid Table 7 Colorful"/>
  <w:LsdException Locked="false" Priority="46"
   Name="Grid Table 1 Light Accent 1"/>
  <w:LsdException Locked="false" Priority="47" Name="Grid Table 2 Accent 1"/>
  <w:LsdException Locked="false" Priority="48" Name="Grid Table 3 Accent 1"/>
  <w:LsdException Locked="false" Priority="49" Name="Grid Table 4 Accent 1"/>
  <w:LsdException Locked="false" Priority="50" Name="Grid Table 5 Dark Accent 1"/>
  <w:LsdException Locked="false" Priority="51"
   Name="Grid Table 6 Colorful Accent 1"/>
  <w:LsdException Locked="false" Priority="52"
   Name="Grid Table 7 Colorful Accent 1"/>
  <w:LsdException Locked="false" Priority="46"
   Name="Grid Table 1 Light Accent 2"/>
  <w:LsdException Locked="false" Priority="47" Name="Grid Table 2 Accent 2"/>
  <w:LsdException Locked="false" Priority="48" Name="Grid Table 3 Accent 2"/>
  <w:LsdException Locked="false" Priority="49" Name="Grid Table 4 Accent 2"/>
  <w:LsdException Locked="false" Priority="50" Name="Grid Table 5 Dark Accent 2"/>
  <w:LsdException Locked="false" Priority="51"
   Name="Grid Table 6 Colorful Accent 2"/>
  <w:LsdException Locked="false" Priority="52"
   Name="Grid Table 7 Colorful Accent 2"/>
  <w:LsdException Locked="false" Priority="46"
   Name="Grid Table 1 Light Accent 3"/>
  <w:LsdException Locked="false" Priority="47" Name="Grid Table 2 Accent 3"/>
  <w:LsdException Locked="false" Priority="48" Name="Grid Table 3 Accent 3"/>
  <w:LsdException Locked="false" Priority="49" Name="Grid Table 4 Accent 3"/>
  <w:LsdException Locked="false" Priority="50" Name="Grid Table 5 Dark Accent 3"/>
  <w:LsdException Locked="false" Priority="51"
   Name="Grid Table 6 Colorful Accent 3"/>
  <w:LsdException Locked="false" Priority="52"
   Name="Grid Table 7 Colorful Accent 3"/>
  <w:LsdException Locked="false" Priority="46"
   Name="Grid Table 1 Light Accent 4"/>
  <w:LsdException Locked="false" Priority="47" Name="Grid Table 2 Accent 4"/>
  <w:LsdException Locked="false" Priority="48" Name="Grid Table 3 Accent 4"/>
  <w:LsdException Locked="false" Priority="49" Name="Grid Table 4 Accent 4"/>
  <w:LsdException Locked="false" Priority="50" Name="Grid Table 5 Dark Accent 4"/>
  <w:LsdException Locked="false" Priority="51"
   Name="Grid Table 6 Colorful Accent 4"/>
  <w:LsdException Locked="false" Priority="52"
   Name="Grid Table 7 Colorful Accent 4"/>
  <w:LsdException Locked="false" Priority="46"
   Name="Grid Table 1 Light Accent 5"/>
  <w:LsdException Locked="false" Priority="47" Name="Grid Table 2 Accent 5"/>
  <w:LsdException Locked="false" Priority="48" Name="Grid Table 3 Accent 5"/>
  <w:LsdException Locked="false" Priority="49" Name="Grid Table 4 Accent 5"/>
  <w:LsdException Locked="false" Priority="50" Name="Grid Table 5 Dark Accent 5"/>
  <w:LsdException Locked="false" Priority="51"
   Name="Grid Table 6 Colorful Accent 5"/>
  <w:LsdException Locked="false" Priority="52"
   Name="Grid Table 7 Colorful Accent 5"/>
  <w:LsdException Locked="false" Priority="46"
   Name="Grid Table 1 Light Accent 6"/>
  <w:LsdException Locked="false" Priority="47" Name="Grid Table 2 Accent 6"/>
  <w:LsdException Locked="false" Priority="48" Name="Grid Table 3 Accent 6"/>
  <w:LsdException Locked="false" Priority="49" Name="Grid Table 4 Accent 6"/>
  <w:LsdException Locked="false" Priority="50" Name="Grid Table 5 Dark Accent 6"/>
  <w:LsdException Locked="false" Priority="51"
   Name="Grid Table 6 Colorful Accent 6"/>
  <w:LsdException Locked="false" Priority="52"
   Name="Grid Table 7 Colorful Accent 6"/>
  <w:LsdException Locked="false" Priority="46" Name="List Table 1 Light"/>
  <w:LsdException Locked="false" Priority="47" Name="List Table 2"/>
  <w:LsdException Locked="false" Priority="48" Name="List Table 3"/>
  <w:LsdException Locked="false" Priority="49" Name="List Table 4"/>
  <w:LsdException Locked="false" Priority="50" Name="List Table 5 Dark"/>
  <w:LsdException Locked="false" Priority="51" Name="List Table 6 Colorful"/>
  <w:LsdException Locked="false" Priority="52" Name="List Table 7 Colorful"/>
  <w:LsdException Locked="false" Priority="46"
   Name="List Table 1 Light Accent 1"/>
  <w:LsdException Locked="false" Priority="47" Name="List Table 2 Accent 1"/>
  <w:LsdException Locked="false" Priority="48" Name="List Table 3 Accent 1"/>
  <w:LsdException Locked="false" Priority="49" Name="List Table 4 Accent 1"/>
  <w:LsdException Locked="false" Priority="50" Name="List Table 5 Dark Accent 1"/>
  <w:LsdException Locked="false" Priority="51"
   Name="List Table 6 Colorful Accent 1"/>
  <w:LsdException Locked="false" Priority="52"
   Name="List Table 7 Colorful Accent 1"/>
  <w:LsdException Locked="false" Priority="46"
   Name="List Table 1 Light Accent 2"/>
  <w:LsdException Locked="false" Priority="47" Name="List Table 2 Accent 2"/>
  <w:LsdException Locked="false" Priority="48" Name="List Table 3 Accent 2"/>
  <w:LsdException Locked="false" Priority="49" Name="List Table 4 Accent 2"/>
  <w:LsdException Locked="false" Priority="50" Name="List Table 5 Dark Accent 2"/>
  <w:LsdException Locked="false" Priority="51"
   Name="List Table 6 Colorful Accent 2"/>
  <w:LsdException Locked="false" Priority="52"
   Name="List Table 7 Colorful Accent 2"/>
  <w:LsdException Locked="false" Priority="46"
   Name="List Table 1 Light Accent 3"/>
  <w:LsdException Locked="false" Priority="47" Name="List Table 2 Accent 3"/>
  <w:LsdException Locked="false" Priority="48" Name="List Table 3 Accent 3"/>
  <w:LsdException Locked="false" Priority="49" Name="List Table 4 Accent 3"/>
  <w:LsdException Locked="false" Priority="50" Name="List Table 5 Dark Accent 3"/>
  <w:LsdException Locked="false" Priority="51"
   Name="List Table 6 Colorful Accent 3"/>
  <w:LsdException Locked="false" Priority="52"
   Name="List Table 7 Colorful Accent 3"/>
  <w:LsdException Locked="false" Priority="46"
   Name="List Table 1 Light Accent 4"/>
  <w:LsdException Locked="false" Priority="47" Name="List Table 2 Accent 4"/>
  <w:LsdException Locked="false" Priority="48" Name="List Table 3 Accent 4"/>
  <w:LsdException Locked="false" Priority="49" Name="List Table 4 Accent 4"/>
  <w:LsdException Locked="false" Priority="50" Name="List Table 5 Dark Accent 4"/>
  <w:LsdException Locked="false" Priority="51"
   Name="List Table 6 Colorful Accent 4"/>
  <w:LsdException Locked="false" Priority="52"
   Name="List Table 7 Colorful Accent 4"/>
  <w:LsdException Locked="false" Priority="46"
   Name="List Table 1 Light Accent 5"/>
  <w:LsdException Locked="false" Priority="47" Name="List Table 2 Accent 5"/>
  <w:LsdException Locked="false" Priority="48" Name="List Table 3 Accent 5"/>
  <w:LsdException Locked="false" Priority="49" Name="List Table 4 Accent 5"/>
  <w:LsdException Locked="false" Priority="50" Name="List Table 5 Dark Accent 5"/>
  <w:LsdException Locked="false" Priority="51"
   Name="List Table 6 Colorful Accent 5"/>
  <w:LsdException Locked="false" Priority="52"
   Name="List Table 7 Colorful Accent 5"/>
  <w:LsdException Locked="false" Priority="46"
   Name="List Table 1 Light Accent 6"/>
  <w:LsdException Locked="false" Priority="47" Name="List Table 2 Accent 6"/>
  <w:LsdException Locked="false" Priority="48" Name="List Table 3 Accent 6"/>
  <w:LsdException Locked="false" Priority="49" Name="List Table 4 Accent 6"/>
  <w:LsdException Locked="false" Priority="50" Name="List Table 5 Dark Accent 6"/>
  <w:LsdException Locked="false" Priority="51"
   Name="List Table 6 Colorful Accent 6"/>
  <w:LsdException Locked="false" Priority="52"
   Name="List Table 7 Colorful Accent 6"/>
 </w:LatentStyles>
</xml><![endif]--><p>&nbsp;</p><!--[if gte mso 10]>
<style>
 /* Style Definitions */
table.MsoNormalTable
	{mso-style-name:"Table Normal";
	mso-tstyle-rowband-size:0;
	mso-tstyle-colband-size:0;
	mso-style-noshow:yes;
	mso-style-priority:99;
	mso-style-parent:"";
	mso-padding-alt:0in 5.4pt 0in 5.4pt;
	mso-para-margin-top:0in;
	mso-para-margin-right:0in;
	mso-para-margin-bottom:10.0pt;
	mso-para-margin-left:0in;
	line-height:115%;
	mso-pagination:widow-orphan;
	font-size:11.0pt;
	font-family:Calibri;
	color:black;}
</style>
<![endif]--><p>&nbsp;</p><!--StartFragment--><p><strong><span style="font-size: 11.0pt; line-height: 115%; font-family: Calibri; mso-fareast-font-family: Calibri; mso-bidi-font-family: Calibri; mso-ansi-language: EN-US; mso-fareast-language: EN-US; mso-bidi-language: AR-SA;">The Playlist has thoughtfully been put together with explicit links to formative assessment.</span></strong></p><!--EndFragment-->',
    'format' => 'full_html',
  );
  $export['qc_78306_criteria_2_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_78306_criteria_num';
  $strongarm->value = '2';
  $export['qc_78306_criteria_num'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_78306_help';
  $strongarm->value = array(
    'value' => '<p>Review the following Playlist resource files using the Quality Criteria for Instructional Playlists below:</p><p><a href="/sites/all/themes/custom/SBAC/workflow_resources/Playlist_Quality_Criteria_Review_Guide_June2016.pdf">Educator Learning Guide and Resource Playlist </a></p><p><a href="/sites/all/themes/custom/SBAC/workflow_resources/Cover_Profile_Guide_Playlists_June2016.pdf">Cover Profile (About This Resource) </a></p><p>Do NOT review the individual resources included in the Playlist. They are posted in the Digital Library and have already gone through Gatekeeping and Quality Criteria reviews.</p>',
    'format' => 'full_html',
  );
  $export['qc_78306_help'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_78686_criteria_1_description';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_78686_criteria_1_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_78686_criteria_1_desc_state';
  $strongarm->value = 'collapsed';
  $export['qc_78686_criteria_1_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_78686_criteria_1_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_78686_criteria_1_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_78686_criteria_1_title';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_78686_criteria_1_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_78686_criteria_2_description';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_78686_criteria_2_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_78686_criteria_2_desc_state';
  $strongarm->value = 'collapsed';
  $export['qc_78686_criteria_2_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_78686_criteria_2_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_78686_criteria_2_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_78686_criteria_2_title';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_78686_criteria_2_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_78686_criteria_num';
  $strongarm->value = '2';
  $export['qc_78686_criteria_num'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_78686_help';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_78686_help'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_1_description';
  $strongarm->value = array(
    'value' => '<p>+ The resource clarifies intended learning that is based on the Common Core State Standards for ELA or Mathematics (e.g., mathematical practices, portrait of the reader, interdisciplinary, etc.).</p><p>+ The resource explicitly references important foundational skills.&nbsp;</p>',
    'format' => 'full_html',
  );
  $export['qc_84_criteria_1_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_1_desc_state';
  $strongarm->value = 'expanded';
  $export['qc_84_criteria_1_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_1_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_84_criteria_1_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_1_title';
  $strongarm->value = array(
    'value' => '<p>[IR] Aligns with the intent of the Common Core State Standards&nbsp;</p>',
    'format' => 'full_html',
  );
  $export['qc_84_criteria_1_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_2_description';
  $strongarm->value = array(
    'value' => '<p>+ Clarify Intended Learning</p><p style="padding-left: 30px;">-- The resource clearly articulates learning goals for students that reflect the Common Core State Standards.</p><p style="padding-left: 30px;">-- The resource clearly articulates success criteria for students.</p><p style="padding-left: 30px;">-- The resource is designed coherently, so that all content aligns to learning goals and success criteria.</p><p>+ Elicit Evidence</p><p style="padding-left: 30px;">-- The resource contains one or more strategies or methods to help students elicit rich, ongoing, instructionally useful evidence of student learning.</p><p>+ Interpret Evidence</p><p style="padding-left: 30px;">-- The resource helps students analyze or interpret one or more sources of evidence generated as part of their coursework (e.g., in class, homework, field study).</p><p>+ Act on Evidence</p><p style="padding-left: 30px;">-- The resource helps educators and/or students act on one or more sources of evidence.</p><p>+ The resource promotes student engagement and accountability as a learner (e.g., self-regulation, student choice, metacognition, strategic learner perspective).</p>',
    'format' => 'full_html',
  );
  $export['qc_84_criteria_2_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_2_desc_state';
  $strongarm->value = 'expanded';
  $export['qc_84_criteria_2_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_2_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_84_criteria_2_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_2_title';
  $strongarm->value = array(
    'value' => '<p>[IR] Incorporates high-quality formative assessment practice(s)</p>',
    'format' => 'full_html',
  );
  $export['qc_84_criteria_2_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_3_description';
  $strongarm->value = array(
    'value' => '<p>+ The content in the resource is free from errors.</p><p>+ The resource uses research-based instructional strategies and promising practices for the intended student population (e.g., English language learners, general education, gifted and talented, students with disabilities).</p><p>+ The resource uses strategies, materials, and supporting standards (e.g., language proficiency standards) that help students meet the Common Core State Standards.&nbsp;</p><p>+ The resource is developmentally appropriate for the intended audience.</p><p>+ The resource supports educators in facilitating high-cognitive-demand tasks and learning experiences for all students.</p><p>+ The resource is complete enough so that educators can integrate the practices into their instruction (i.e., no major components or materials are missing).</p><p>+ The resource identifies the materials (and associated costs) necessary to implement the instruction effectively.&nbsp;</p><p>+ Mathematics resources, for example:</p><p style="padding-left: 30px;">-- The task/activity in the resource leverages the mathematical practices to teach the content.</p><p style="padding-left: 30px;">-- The resource focuses deeply on the concepts priortized by the standards.</p><p style="padding-left: 30px;">-- The task/lesson in the resource provides opportunities for students to build connections or relationships among mathematical ideas, encouraging links to other major topics within the grade level and across grade levels.</p><p style="padding-left: 30px;">-- The resource actively supports the development of conceptual understanding, as well as practical application and fluency.</p><p>+ ELA resources, for example:</p><p style="padding-left: 30px;">-- The resource builds content knowledge through culturally and/or personally relevant text in print and/or digital formats.</p><p style="padding-left: 30px;">-- The resource emphasizes writing and/or multimodal composition that uses source-based evidence to inform or argue.</p><p style="padding-left: 30px;">-- The resource enables students to have rich and rigorous conversations about a common text and/or set of texts.</p><p style="padding-left: 30px;">-- The resource engages students in research/inquiry to investigate topics and to analyze, integrate, and present information.</p><p style="padding-left: 30px;">-- The resource allows students to build the academic language needed to access more complex text and develop disciplinary literacy practices.&nbsp;</p>',
    'format' => 'full_html',
  );
  $export['qc_84_criteria_3_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_3_desc_state';
  $strongarm->value = 'expanded';
  $export['qc_84_criteria_3_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_3_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_84_criteria_3_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_3_title';
  $strongarm->value = array(
    'value' => '<p>[IR] Contains accurate, complete, high-quality curriculum and instruction&nbsp;</p>',
    'format' => 'full_html',
  );
  $export['qc_84_criteria_3_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_4_description';
  $strongarm->value = array(
    'value' => '<p>+ The resource reflects one or more principles of Universal Design for Learning (e.g., multiple means of representation, action and expression, engagement).</p><p>+ The resource is accessible to, or can be modified for, a range of students, including students with disabilities, English language learners, culturally diverse students, and students with gifts and talents.</p><p>+ The resource supports instruction for a range of learners. It can be differentiated based on student readiness, interest, learning style, background knowledge, English language proficiency.</p><p>+ The resource provides supplemental materials and strategies for students who need more or less support in the specific content or learning process.</p><p>+ The resource can be used and/or adapted in multiple teaching and school contexts.</p>',
    'format' => 'full_html',
  );
  $export['qc_84_criteria_4_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_4_desc_state';
  $strongarm->value = 'expanded';
  $export['qc_84_criteria_4_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_4_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_84_criteria_4_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_4_title';
  $strongarm->value = array(
    'value' => '<p>[IR] Reflects learner differences and supports personalized learning</p>',
    'format' => 'full_html',
  );
  $export['qc_84_criteria_4_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_5_description';
  $strongarm->value = array(
    'value' => '<p>+ The resource is self-explanatory or easy to use for teachers and students.</p><p>+ The resource engages the student through stimulating and challenging content, and/or creative, inventive formats.</p>',
    'format' => 'full_html',
  );
  $export['qc_84_criteria_5_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_5_desc_state';
  $strongarm->value = 'expanded';
  $export['qc_84_criteria_5_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_5_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_84_criteria_5_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_5_title';
  $strongarm->value = array(
    'value' => '<p>[IR] Demonstrates utility, engagement, and user-friendliness</p>',
    'format' => 'full_html',
  );
  $export['qc_84_criteria_5_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_6_description';
  $strongarm->value = array(
    'value' => '<p>+ The resource integrates technology and media in a way that connects explicitly to the identified learning goals. The technology/media support the student in one or more steps of the formative process (i.e., Clarify Intended Learning, Elicit Evidence, Interpret Evidence, Act on Evidence).</p><p>+ The technology and media support access to text and other curriculum materials.</p><p>+ The technology and media are developmentally appropriate.</p><p>+ The technology and media are accessible by a range of students.</p>',
    'format' => 'full_html',
  );
  $export['qc_84_criteria_6_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_6_desc_state';
  $strongarm->value = 'expanded';
  $export['qc_84_criteria_6_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_6_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_84_criteria_6_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_6_title';
  $strongarm->value = array(
    'value' => '<p>[IR] Integrates media and technology effectively</p>',
    'format' => 'full_html',
  );
  $export['qc_84_criteria_6_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_criteria_num';
  $strongarm->value = '6';
  $export['qc_84_criteria_num'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_84_help';
  $strongarm->value = array(
    'value' => '<p style="font-family: Arial, Helvetica, sans-serif;">This resource is ready for a Quality Criteria review. Please review the&nbsp;<a href="/system/files/resource/Quality-Criteria-FAQ.pdf" target="_blank">Quality Criteria FAQ</a>,&nbsp;<a href="/system/files/resource/Appx-A-UDL.pdf" target="_blank">Universal Design for Learning (UDL) guide</a>, and/or&nbsp;<a style="color: #3b953f; outline: #000000; cursor: pointer;" href="/system/files/resource/Appx-B-Prof-Learning.pdf" target="_blank">Professional Learning Overview</a>&nbsp;for more information on how to complete this step. At any point during the 72-hour window allocated to this step you can click the “Save and Close” button to save your work and return later to complete it. &nbsp;If you are unable to finish the review within 72 hours, click “Cancel Review” and the resource will be returned to the queue.&nbsp;</p><p style="font-family: Arial, Helvetica, sans-serif;">For additional assistance, visit the Help section.</p>',
    'format' => 'full_html',
  );
  $export['qc_84_help'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_85_criteria_1_description';
  $strongarm->value = array(
    'value' => '<p>+ The content of the resource is consistent with current research.</p><p>+ The design of the resource reflects principles of effective professional learning , including:</p><p style="padding-left: 30px;">-- Aligns outcomes with educator practice and student standards</p><p style="padding-left: 30px;">-- Supports change in instructional practice</p><p style="padding-left: 30px;">--Uses a variety of sources and types of student, educator, and system data to plan, assess, and evaluate professional learning</p><p style="padding-left: 30px;">-- Takes educators through practices similar to those that it expects the educator to implement with students&nbsp;</p><p style="padding-left: 30px;">-- Is respectful of the experience and purpose that adults bring to their learning</p><p style="padding-left: 30px;">-- Promotes shared goals, collaboration, and effective communication within learning communities</p><p style="padding-left: 30px;">-- Provides opportunities for reflective practice</p><p style="padding-left: 30px;">-- Enables educators to apply new skills and concepts in the context of their practice by providing multiple opportunities to try, reflect, and move toward new practices</p><p style="padding-left: 30px;">-- Demonstrates the productive, respectful use of artifacts from practice, such as video and samples of student work</p><p>+ The resource includes evidence of positive impact on educator practice or otherwise demonstrates promise.</p>',
    'format' => 'full_html',
  );
  $export['qc_85_criteria_1_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_85_criteria_1_desc_state';
  $strongarm->value = 'expanded';
  $export['qc_85_criteria_1_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_85_criteria_1_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_85_criteria_1_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_85_criteria_1_title';
  $strongarm->value = array(
    'value' => '<p>[PL] Reflects research and/or the principles of effective professional learning</p>',
    'format' => 'full_html',
  );
  $export['qc_85_criteria_1_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_85_criteria_2_description';
  $strongarm->value = array(
    'value' => '<p>+ Clarify Intended Learning</p><p style="padding-left: 30px;">-- The resource clearly articulates learning goals that reflect the Common Core State Standards.</p><p style="padding-left: 30px;">-- The resource clearly articulates success criteria for the educator.</p><p style="padding-left: 30px;">-- The resource is designed coherently, so that all content aligns to learning goals and success criteria.</p><p>+ Elicit Evidence</p><p style="padding-left: 30px;">-- The resource includes tasks and/or strategies to elicit evidence of learning (e.g., self-assessments, self-reflection, educator-directed).&nbsp;</p><p>+ Interpret Evidence</p><p style="padding-left: 30px;">-- The resource provides a way (e.g. method, model, process) to analyze or interpret evidence.</p><p>+ Act on Evidence</p><p style="padding-left: 30px;">-- The resource provides opportunities or recommendations for responsive action to evidence (e.g. provide feedback to participants, suggest grouping of participants, create action plans, set goals, revise learning experience based on analysis of evidence).</p><p>+ The resource enables students to actively engage in the assessment and learning process.&nbsp;</p>',
    'format' => 'full_html',
  );
  $export['qc_85_criteria_2_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_85_criteria_2_desc_state';
  $strongarm->value = 'expanded';
  $export['qc_85_criteria_2_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_85_criteria_2_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_85_criteria_2_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_85_criteria_2_title';
  $strongarm->value = array(
    'value' => '<p>[PL] Incorporates high-quality formative assessment practice(s)</p>',
    'format' => 'full_html',
  );
  $export['qc_85_criteria_2_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_85_criteria_3_description';
  $strongarm->value = array(
    'value' => '<p>+ The resource reflects one or more principles of Universal Design for Learning (e.g., multiple means of representation, action and expression, engagement).</p><p>+ The resource is accessible to, or can be modified for, a range of educators, including educators with disabilities and culturally diverse educators.</p><p>+ The resource supports a range of educators. It can be differentiated based on educator readiness, interest, or learning style.</p><p>+ The resource provides supplemental materials and strategies for educators who would like more or less support in the specific topic or content.</p><p>+ The resource can be used and/or adapted in multiple teaching and school contexts.</p><p>+ The resource reflects diversity in the educators and students it profiles.</p><p>+ The resource can be easily adapted for a variety of formats (e.g., PLCs/collaborative learning teams, individuals, online learning).</p>',
    'format' => 'full_html',
  );
  $export['qc_85_criteria_3_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_85_criteria_3_desc_state';
  $strongarm->value = 'expanded';
  $export['qc_85_criteria_3_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_85_criteria_3_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_85_criteria_3_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_85_criteria_3_title';
  $strongarm->value = array(
    'value' => '<p>[PL] Reflects learner differences and supports personalized learning</p>',
    'format' => 'full_html',
  );
  $export['qc_85_criteria_3_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_85_criteria_4_description';
  $strongarm->value = array(
    'value' => '<p>+ The resource is self-explanatory or easy to use.</p><p>+ The resource engages the educator through stimulating and challenging content, and/or creative, inventive formats.</p>',
    'format' => 'full_html',
  );
  $export['qc_85_criteria_4_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_85_criteria_4_desc_state';
  $strongarm->value = 'expanded';
  $export['qc_85_criteria_4_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_85_criteria_4_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_85_criteria_4_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_85_criteria_4_title';
  $strongarm->value = array(
    'value' => '<p>[PL] Demonstrates utility, engagement, and user-friendliness</p>',
    'format' => 'full_html',
  );
  $export['qc_85_criteria_4_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_85_criteria_5_description';
  $strongarm->value = array(
    'value' => '<p>+ The resource integrates technology in a way that increases the educator’s understanding and teaching of the Common Core State Standards.</p><p>+ The technology/media support the educator in one or more steps of the formative assessment process (i.e., Clarify Intended Learning, Elicit Evidence, Interpret Evidence, Act on Evidence).</p><p>+ The technology/media are accessible by a range of educators.</p>',
    'format' => 'full_html',
  );
  $export['qc_85_criteria_5_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_85_criteria_5_desc_state';
  $strongarm->value = 'expanded';
  $export['qc_85_criteria_5_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_85_criteria_5_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_85_criteria_5_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_85_criteria_5_title';
  $strongarm->value = array(
    'value' => '<p>[PL] Integrates media and technology effectively</p>',
    'format' => 'full_html',
  );
  $export['qc_85_criteria_5_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_85_criteria_num';
  $strongarm->value = '5';
  $export['qc_85_criteria_num'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_85_help';
  $strongarm->value = array(
    'value' => '<p style="font-family: Arial, Helvetica, sans-serif;">This resource is ready for a Quality Criteria review. Please review the&nbsp;<a href="/system/files/resource/Quality-Criteria-FAQ.pdf" target="_blank">Quality Criteria FAQ</a>,&nbsp;<a href="/system/files/resource/Appx-A-UDL.pdf" target="_blank">Universal Design for Learning (UDL) guide</a>, and/or&nbsp;<a style="color: #3b953f; outline: #000000; cursor: pointer;" href="/system/files/resource/Appx-B-Prof-Learning.pdf" target="_blank">Professional Learning Overview</a>&nbsp;for more information on how to complete this step. At any point during the 72-hour window allocated to this step you can click the “Save and Close” button to save your work and return later to complete it. &nbsp;If you are unable to finish the review within 72 hours, click “Cancel Review” and the resource will be returned to the queue.&nbsp;</p><p style="font-family: Arial, Helvetica, sans-serif;">For additional assistance, visit the Help section.</p>',
    'format' => 'full_html',
  );
  $export['qc_85_help'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_10_description';
  $strongarm->value = array(
    'value' => '<p style="font-family: Arial, Helvetica, sans-serif;">+ The resource is self-explanatory or easy to use for teachers and students.</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The resource engages the student through stimulating and challenging content, and/or creative, inventive formats.</p>',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_10_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_10_desc_state';
  $strongarm->value = 'expanded';
  $export['qc_86_criteria_10_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_10_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_10_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_10_title';
  $strongarm->value = array(
    'value' => '<p>[IR] Demonstrates utility, engagement, and user-friendliness</p>',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_10_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_11_description';
  $strongarm->value = array(
    'value' => '<p style="font-family: Arial, Helvetica, sans-serif;">+ The resource integrates technology and media in a way that connects explicitly to the identified learning goals. The technology/media support the student in one or more steps of the formative process (i.e., Clarify Intended Learning, Elicit Evidence, Interpret Evidence, Act on Evidence).</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The technology and media support access to text and other curriculum materials.</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The technology and media are developmentally appropriate.</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The technology and media are accessible by a range of students.</p>',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_11_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_11_desc_state';
  $strongarm->value = 'expanded';
  $export['qc_86_criteria_11_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_11_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_11_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_11_title';
  $strongarm->value = array(
    'value' => '<p>[IR] Integrates media and technology effectively</p>',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_11_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_1_description';
  $strongarm->value = array(
    'value' => '<p style="font-family: Arial, Helvetica, sans-serif;">+ The content of the resource is consistent with current research.</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The design of the resource reflects principles of effective professional learning , including:</p><p style="padding-left: 30px; font-family: Arial, Helvetica, sans-serif;">-- Aligns outcomes with educator practice and student standards</p><p style="padding-left: 30px; font-family: Arial, Helvetica, sans-serif;">-- Supports change in instructional practice</p><p style="padding-left: 30px; font-family: Arial, Helvetica, sans-serif;">--Uses a variety of sources and types of student, educator, and system data to plan, assess, and evaluate professional learning</p><p style="padding-left: 30px; font-family: Arial, Helvetica, sans-serif;">-- Takes educators through practices similar to those that it expects the educator to implement with students&nbsp;</p><p style="padding-left: 30px; font-family: Arial, Helvetica, sans-serif;">-- Is respectful of the experience and purpose that adults bring to their learning</p><p style="padding-left: 30px; font-family: Arial, Helvetica, sans-serif;">-- Promotes shared goals, collaboration, and effective communication within learning communities</p><p style="padding-left: 30px; font-family: Arial, Helvetica, sans-serif;">-- Provides opportunities for reflective practice</p><p style="padding-left: 30px; font-family: Arial, Helvetica, sans-serif;">-- Enables educators to apply new skills and concepts in the context of their practice by providing multiple opportunities to try, reflect, and move toward new practices</p><p style="padding-left: 30px; font-family: Arial, Helvetica, sans-serif;">-- Demonstrates the productive, respectful use of artifacts from practice, such as video and samples of student work</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The resource includes evidence of positive impact on educator practice or otherwise demonstrates promise.</p>',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_1_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_1_desc_state';
  $strongarm->value = 'expanded';
  $export['qc_86_criteria_1_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_1_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_1_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_1_title';
  $strongarm->value = array(
    'value' => '<p>[PL] Reflects research and/or the principles of effective professional learning</p>',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_1_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_2_description';
  $strongarm->value = array(
    'value' => '<p style="font-family: Arial, Helvetica, sans-serif;">+ Clarify Intended Learning</p><p style="padding-left: 30px; font-family: Arial, Helvetica, sans-serif;">-- The resource clearly articulates learning goals that reflect the Common Core State Standards.</p><p style="padding-left: 30px; font-family: Arial, Helvetica, sans-serif;">-- The resource clearly articulates success criteria for the educator.</p><p style="padding-left: 30px; font-family: Arial, Helvetica, sans-serif;">-- The resource is designed coherently, so that all content aligns to learning goals and success criteria.</p><p style="font-family: Arial, Helvetica, sans-serif;">+ Elicit Evidence</p><p style="padding-left: 30px; font-family: Arial, Helvetica, sans-serif;">-- The resource includes tasks and/or strategies to elicit evidence of learning (e.g., self-assessments, self-reflection, educator-directed).&nbsp;</p><p style="font-family: Arial, Helvetica, sans-serif;">+ Interpret Evidence</p><p style="padding-left: 30px; font-family: Arial, Helvetica, sans-serif;">-- The resource provides a way (e.g. method, model, process) to analyze or interpret evidence.</p><p style="font-family: Arial, Helvetica, sans-serif;">+ Act on Evidence</p><p style="padding-left: 30px; font-family: Arial, Helvetica, sans-serif;">-- The resource provides opportunities or recommendations for responsive action to evidence (e.g. provide feedback to participants, suggest grouping of participants, create action plans, set goals, revise learning experience based on analysis of evidence).</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The resource enables students to actively engage in the assessment and learning process.&nbsp;</p>',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_2_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_2_desc_state';
  $strongarm->value = 'expanded';
  $export['qc_86_criteria_2_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_2_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_2_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_2_title';
  $strongarm->value = array(
    'value' => '<p>[PL] Incorporates high-quality formative assessment practice(s)</p>',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_2_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_3_description';
  $strongarm->value = array(
    'value' => '<p style="font-family: Arial, Helvetica, sans-serif;">+ The resource reflects one or more principles of Universal Design for Learning (e.g., multiple means of representation, action and expression, engagement).</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The resource is accessible to, or can be modified for, a range of educators, including educators with disabilities and culturally diverse educators.</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The resource supports a range of educators. It can be differentiated based on educator readiness, interest, or learning style.</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The resource provides supplemental materials and strategies for educators who would like more or less support in the specific topic or content.</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The resource can be used and/or adapted in multiple teaching and school contexts.</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The resource reflects diversity in the educators and students it profiles.</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The resource can be easily adapted for a variety of formats (e.g., PLCs/collaborative learning teams, individuals, online learning).</p>',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_3_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_3_desc_state';
  $strongarm->value = 'expanded';
  $export['qc_86_criteria_3_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_3_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_3_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_3_title';
  $strongarm->value = array(
    'value' => '<p>[PL] Reflects learner differences and supports personalized learning</p>',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_3_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_4_description';
  $strongarm->value = array(
    'value' => '<p style="font-family: Arial, Helvetica, sans-serif;">+ The resource is self-explanatory or easy to use.</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The resource engages the educator through stimulating and challenging content, and/or creative, inventive formats.</p>',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_4_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_4_desc_state';
  $strongarm->value = 'expanded';
  $export['qc_86_criteria_4_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_4_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_4_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_4_title';
  $strongarm->value = array(
    'value' => '<p>[PL] Demonstrates utility, engagement, and user-friendliness</p>',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_4_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_5_description';
  $strongarm->value = array(
    'value' => '<p style="font-family: Arial, Helvetica, sans-serif;">+ The resource integrates technology in a way that increases the educator’s understanding and teaching of the Common Core State Standards.</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The technology/media support the educator in one or more steps of the formative assessment process (i.e., Clarify Intended Learning, Elicit Evidence, Interpret Evidence, Act on Evidence).</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The technology/media are accessible by a range of educators.</p>',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_5_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_5_desc_state';
  $strongarm->value = 'expanded';
  $export['qc_86_criteria_5_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_5_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_5_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_5_title';
  $strongarm->value = array(
    'value' => '<p>[PL] Integrates media and technology effectively</p>',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_5_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_6_description';
  $strongarm->value = array(
    'value' => '<p style="font-family: Arial, Helvetica, sans-serif;">+ The resource clarifies intended learning that is based on the Common Core State Standards for ELA or Mathematics (e.g., mathematical practices, portrait of the reader, interdisciplinary, etc.).</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The resource explicitly references important foundational skills.&nbsp;</p>',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_6_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_6_desc_state';
  $strongarm->value = 'expanded';
  $export['qc_86_criteria_6_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_6_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_6_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_6_title';
  $strongarm->value = array(
    'value' => '<p>[IR] Aligns with the intent of the Common Core State Standards&nbsp;</p>',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_6_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_7_description';
  $strongarm->value = array(
    'value' => '<p style="font-family: Arial, Helvetica, sans-serif;">+ Clarify Intended Learning</p><p style="padding-left: 30px;">-- The resource clearly articulates learning goals for students that reflect the Common Core State Standards.</p><p style="padding-left: 30px;">-- The resource clearly articulates success criteria for students.</p><p style="padding-left: 30px;">-- The resource is designed coherently, so that all content aligns to learning goals and success criteria.</p><p style="font-family: Arial, Helvetica, sans-serif;">+ Elicit Evidence</p><p style="padding-left: 30px;">-- The resource contains one or more strategies or methods to help students elicit rich, ongoing, instructionally useful evidence of student learning.</p><p style="font-family: Arial, Helvetica, sans-serif;">+ Interpret Evidence</p><p style="padding-left: 30px;">-- The resource helps students analyze or interpret one or more sources of evidence generated as part of their coursework (e.g., in class, homework, field study).</p><p style="font-family: Arial, Helvetica, sans-serif;">+ Act on Evidence</p><p style="padding-left: 30px;">-- The resource helps educators and/or students act on one or more sources of evidence.</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The resource promotes student engagement and accountability as a learner (e.g., self-regulation, student choice, metacognition, strategic learner perspective).</p>',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_7_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_7_desc_state';
  $strongarm->value = 'expanded';
  $export['qc_86_criteria_7_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_7_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_7_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_7_title';
  $strongarm->value = array(
    'value' => '<p>[IR] Incorporates high-quality formative assessment practices</p>',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_7_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_8_description';
  $strongarm->value = array(
    'value' => '<p style="font-family: Arial, Helvetica, sans-serif;">+ The content in the resource is free from errors.</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The resource uses research-based instructional strategies and promising practices for the intended student population (e.g., English language learners, general education, gifted and talented, students with disabilities).</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The resource uses strategies, materials, and supporting standards (e.g., language proficiency standards) that help students meet the Common Core State Standards.&nbsp;</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The resource is developmentally appropriate for the intended audience.</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The resource supports educators in facilitating high-cognitive-demand tasks and learning experiences for all students.</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The resource is complete enough so that educators can integrate the practices into their instruction (i.e., no major components or materials are missing).</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The resource identifies the materials (and associated costs) necessary to implement the instruction effectively.&nbsp;</p><p style="font-family: Arial, Helvetica, sans-serif;">+ Mathematics resources, for example:</p><p style="padding-left: 30px;">-- The task/activity in the resource leverages the mathematical practices to teach the content.</p><p style="padding-left: 30px;">-- The resource focuses deeply on the concepts priortized by the standards.</p><p style="padding-left: 30px;">-- The task/lesson in the resource provides opportunities for students to build connections or relationships among mathematical ideas, encouraging links to other major topics within the grade level and across grade levels.</p><p style="padding-left: 30px;">-- The resource actively supports the development of conceptual understanding, as well as practical application and fluency.</p><p style="font-family: Arial, Helvetica, sans-serif;">+ ELA resources, for example:</p><p style="padding-left: 30px;">-- The resource builds content knowledge through culturally and/or personally relevant text in print and/or digital formats.</p><p style="padding-left: 30px;">-- The resource emphasizes writing and/or multimodal composition that uses source-based evidence to inform or argue.</p><p style="padding-left: 30px;">-- The resource enables students to have rich and rigorous conversations about a common text and/or set of texts.</p><p style="padding-left: 30px;">-- The resource engages students in research/inquiry to investigate topics and to analyze, integrate, and present information.</p><p style="padding-left: 30px;">-- The resource allows students to build the academic language needed to access more complex text and develop disciplinary literacy practices.&nbsp;</p>',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_8_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_8_desc_state';
  $strongarm->value = 'expanded';
  $export['qc_86_criteria_8_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_8_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_8_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_8_title';
  $strongarm->value = array(
    'value' => '<p>[IR] Contains accurate, complete, high-quality curriculum and instruction&nbsp;</p>',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_8_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_9_description';
  $strongarm->value = array(
    'value' => '<p style="font-family: Arial, Helvetica, sans-serif;">+ The resource reflects one or more principles of Universal Design for Learning (e.g., multiple means of representation, action and expression, engagement).</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The resource is accessible to, or can be modified for, a range of students, including students with disabilities, English language learners, culturally diverse students, and students with gifts and talents.</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The resource supports instruction for a range of learners. It can be differentiated based on student readiness, interest, learning style, background knowledge, English language proficiency.</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The resource provides supplemental materials and strategies for students who need more or less support in the specific content or learning process.</p><p style="font-family: Arial, Helvetica, sans-serif;">+ The resource can be used and/or adapted in multiple teaching and school contexts.</p>',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_9_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_9_desc_state';
  $strongarm->value = 'expanded';
  $export['qc_86_criteria_9_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_9_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_9_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_9_title';
  $strongarm->value = array(
    'value' => '<p>[IR] Reflects learner differences and supports personalized learning</p>',
    'format' => 'full_html',
  );
  $export['qc_86_criteria_9_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_criteria_num';
  $strongarm->value = '11';
  $export['qc_86_criteria_num'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_86_help';
  $strongarm->value = array(
    'value' => '<p style="font-family: Arial, Helvetica, sans-serif;">This resource is ready for a Quality Criteria review. Please review the&nbsp;<a href="/system/files/resource/Quality-Criteria-FAQ.pdf" target="_blank">Quality Criteria FAQ</a>,&nbsp;<a href="/system/files/resource/Appx-A-UDL.pdf" target="_blank">Universal Design for Learning (UDL) guide</a>, and/or&nbsp;<a style="color: #3b953f; outline: #000000; cursor: pointer;" href="/system/files/resource/Appx-B-Prof-Learning.pdf" target="_blank">Professional Learning Overview</a>&nbsp;for more information on how to complete this step. At any point during the 72-hour window allocated to this step you can click the “Save and Close” button to save your work and return later to complete it. &nbsp;If you are unable to finish the review within 72 hours, click “Cancel Review” and the resource will be returned to the queue.&nbsp;</p><p style="font-family: Arial, Helvetica, sans-serif;">For additional assistance, visit the Help section.</p>',
    'format' => 'full_html',
  );
  $export['qc_86_help'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_level_0';
  $strongarm->value = array(
    'value' => '<p>Not Applicable</p>',
    'format' => 'full_html',
  );
  $export['qc_level_0'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_level_1';
  $strongarm->value = array(
    'value' => '<p>No Evidence</p>',
    'format' => 'full_html',
  );
  $export['qc_level_1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_level_2';
  $strongarm->value = array(
    'value' => '<p>Minimal Evidence</p>',
    'format' => 'full_html',
  );
  $export['qc_level_2'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_level_3';
  $strongarm->value = array(
    'value' => '<p>Partial Evidence</p>',
    'format' => 'full_html',
  );
  $export['qc_level_3'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_level_4';
  $strongarm->value = array(
    'value' => '<p>Adequate Evidence</p>',
    'format' => 'full_html',
  );
  $export['qc_level_4'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_level_5';
  $strongarm->value = array(
    'value' => '<p>Exemplary Evidence</p>',
    'format' => 'full_html',
  );
  $export['qc_level_5'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_rec_0';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_rec_0'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_rec_1';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_rec_1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_rec_2';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_rec_2'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qc_rec_3';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qc_rec_3'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_1_description';
  $strongarm->value = array(
    'value' => '<p><strong>&nbsp;• The resource clarifies intended learning that is based on the Common Core State Standards for ELA or Mathematics (e.g., mathematical practices, portrait of the reader, interdisciplinary, etc.).</strong></p><p><strong>• The resource reflects the Smarter Balanced claims, clusters, and/or targets for the Common Core State Standards.</strong></p><p><strong>• The resource explicitly references precursor and successor skills.&nbsp;</strong></p><p><strong>• The tasks included in the resource meet or exceed the Depth of Knowledge (DOK) levels as indicated in the Item Specification document for the content.</strong></p>',
    'format' => 'full_html',
  );
  $export['qr_84_criteria_1_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_1_desc_state';
  $strongarm->value = 'expanded';
  $export['qr_84_criteria_1_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_1_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_84_criteria_1_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_1_title';
  $strongarm->value = array(
    'value' => '<p>1. Aligns with the intent of the Common Core State Standards&nbsp;</p>',
    'format' => 'full_html',
  );
  $export['qr_84_criteria_1_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_2_description';
  $strongarm->value = array(
    'value' => '<p><strong>• Clarify Intended Learning</strong></p><p>o The resource describes the learning goals and success criteria.</p><p><strong>• Elicit Evidence</strong></p><p>o The resource contains one or more strategies or methods to help educators and/or students elicit rich, ongoing, instructionally useful evidence of student learning.</p><p><strong>• Interpret Evidence</strong></p><p>o The resource helps educators and/or students analyze or interpret one or more sources of evidence generated as part of their coursework (e.g., in class, homework, field study).</p><p><strong>• Act on Evidence</strong></p><p>o The resource helps educators and/or students act on one or more sources of evidence.</p><p><strong>• The resource promotes student engagement and accountability as a learner (e.g., self-regulation, student choice, metacognition, strategic learner perspective).</strong></p>',
    'format' => 'full_html',
  );
  $export['qr_84_criteria_2_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_2_desc_state';
  $strongarm->value = 'expanded';
  $export['qr_84_criteria_2_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_2_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_84_criteria_2_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_2_title';
  $strongarm->value = array(
    'value' => '<p>2.&nbsp;Incorporates high-quality formative assessment practices</p>',
    'format' => 'full_html',
  );
  $export['qr_84_criteria_2_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_3_description';
  $strongarm->value = array(
    'value' => '<p><strong>• The content in the resource is free from errors.</strong></p><p><strong>• The resource uses research-based instructional strategies and promising practices for the intended student population (e.g., English language learners, general education, gifted and talented, students with disabilities).</strong></p><p><strong>• The resource uses strategies, materials, and supporting standards (e.g., language proficiency standards) that help students meet the Common Core State Standards.&nbsp;</strong></p><p><strong>• The resource is developmentally appropriate for the intended audience.</strong></p><p><strong>• The resource supports educators in facilitating high-cognitive-demand tasks and learning experiences for all students.</strong></p><p><strong>• The resource is complete enough so that educators can integrate the practices into their instruction (i.e., no major components or materials are missing).</strong></p><p><strong>• The resource identifies the materials (and associated costs) necessary to implement the instruction effectively.&nbsp;</strong></p><p><strong>For mathematics resources:</strong></p><p>• The task/activity in the resource leverages the mathematical practices to teach the content.</p><p>• The task/lesson in the resource provides opportunities for students to build connections or relationships among mathematical ideas.</p><p><strong>For ELA resources:</strong></p><p>• The resource builds content knowledge through culturally and/or personally relevant text in print and/or digital formats.</p><p>• The resource emphasizes writing and/or multimodal composition that uses source-based evidence to inform or persuade.</p><p>• The resource enables students to have rich and rigorous conversations about a common text and/or set of texts.</p><p>• The resource engages students in research/inquiry to investigate topics and to analyze, integrate, and present information.</p><p>• The resource allows students to build the academic language needed to access more complex text and develop disciplinary literacy practices.&nbsp;</p>',
    'format' => 'full_html',
  );
  $export['qr_84_criteria_3_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_3_desc_state';
  $strongarm->value = 'expanded';
  $export['qr_84_criteria_3_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_3_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_84_criteria_3_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_3_title';
  $strongarm->value = array(
    'value' => '<p>3.&nbsp;Contains accurate, complete, high-quality curriculum and instruction&nbsp;</p>',
    'format' => 'full_html',
  );
  $export['qr_84_criteria_3_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_4_description';
  $strongarm->value = array(
    'value' => '<p><strong>• The resource reflects one or more principles of Universal Design for Learning (e.g., multiple means of representation, action and expression, engagement).</strong></p><p><strong>• The resource is accessible to, or can be modified for, a range of students, including students with disabilities, English language learners, culturally diverse students, and students with gifts and talents.</strong></p><p><strong>• The resource supports instruction for a range of learners. It can be differentiated based on student readiness, interest, learning style, background knowledge, English language proficiency.</strong></p><p><strong>• The resource provides supplemental materials and strategies for students who need more or less support in the specific content or learning process.</strong></p><p><strong>• The resource can be used and/or adapted in multiple teaching and school contexts.</strong></p>',
    'format' => 'full_html',
  );
  $export['qr_84_criteria_4_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_4_desc_state';
  $strongarm->value = 'expanded';
  $export['qr_84_criteria_4_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_4_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_84_criteria_4_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_4_title';
  $strongarm->value = array(
    'value' => '<p>4.&nbsp;Reflects learner differences and supports personalized learning</p>',
    'format' => 'full_html',
  );
  $export['qr_84_criteria_4_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_5_description';
  $strongarm->value = array(
    'value' => '<p><strong>• The resource is self-explanatory or easy to use for teachers and students.</strong></p><p><strong>• The resource engages the student through stimulating and challenging content, and/or creative, inventive formats.</strong></p>',
    'format' => 'full_html',
  );
  $export['qr_84_criteria_5_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_5_desc_state';
  $strongarm->value = 'collapsed';
  $export['qr_84_criteria_5_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_5_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_84_criteria_5_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_5_title';
  $strongarm->value = array(
    'value' => '<p>5.&nbsp;Demonstrates utility, engagement, and user-friendliness</p>',
    'format' => 'full_html',
  );
  $export['qr_84_criteria_5_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_6_description';
  $strongarm->value = array(
    'value' => '<p><strong>• The resource integrates technology and media in a way that connects explicitly to the identified learning targets. The technology/media support the educator and/or student in one or more steps of the formative process (i.e., Clarify Intended Learning, Elicit Evidence, Interpret Evidence, Act on Evidence).</strong></p><p><strong>• The technology and media support access to text and other curriculum materials.</strong></p><p><strong>• The technology and media are developmentally appropriate.</strong></p><p><strong>• The technology and media are accessible by a range of students.</strong></p>',
    'format' => 'full_html',
  );
  $export['qr_84_criteria_6_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_6_desc_state';
  $strongarm->value = 'expanded';
  $export['qr_84_criteria_6_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_6_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_84_criteria_6_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_6_title';
  $strongarm->value = array(
    'value' => '<p>6.&nbsp;Integrates media and technology effectively</p>',
    'format' => 'full_html',
  );
  $export['qr_84_criteria_6_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_criteria_num';
  $strongarm->value = '6';
  $export['qr_84_criteria_num'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_84_help';
  $strongarm->value = array(
    'value' => '<p>If you are unable to complete the review in the timeframe, click “Cancel Review” and the resource will be returned to the queue. If you are in the midst of a review and the 72-hour window is reached, the resource will be returned to the queue. Finally, if you are in the midst of a review and need to step away from the computer, you may save your review for later (as long as the 72-hour window is not reached). For additional assistance, refer to the Help section.</p>',
    'format' => 'full_html',
  );
  $export['qr_84_help'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_85_criteria_1_description';
  $strongarm->value = array(
    'value' => '<p style="font-family: Arial, \'Helvetica sans-serif\';"><strong>• The content of the resource is consistent with current research.</strong></p><p style="font-family: Arial, \'Helvetica sans-serif\';"><strong>• The design of the resource reflects principles of effective professional learning , including:</strong></p><p style="font-family: Arial, \'Helvetica sans-serif\';">o Aligns outcomes with educator practice and student standards</p><p style="font-family: Arial, \'Helvetica sans-serif\';">o Supports change in instructional practice</p><p style="font-family: Arial, \'Helvetica sans-serif\';">o Uses a variety of sources and types of student, educator, and system data to plan, assess, and evaluate professional learning</p><p style="font-family: Arial, \'Helvetica sans-serif\';">o Takes educators through practices similar to those that it expects the educator to implement with students&nbsp;</p><p style="font-family: Arial, \'Helvetica sans-serif\';">o Is respectful of the experience and purpose that adults bring to their learning</p><p style="font-family: Arial, \'Helvetica sans-serif\';">o Promotes shared goals, collaboration, and effective communication within learning communities</p><p style="font-family: Arial, \'Helvetica sans-serif\';">o Provides opportunities for reflective practice</p><p style="font-family: Arial, \'Helvetica sans-serif\';">o Enables educators to apply new skills and concepts in the context of their practice by providing multiple opportunities to try, reflect, and move toward new practices</p><p style="font-family: Arial, \'Helvetica sans-serif\';">o Demonstrates the productive, respectful use of artifacts from practice, such as video and samples of student work</p><p style="font-family: Arial, \'Helvetica sans-serif\';"><strong>• The resource includes evidence of positive impact on educator practice or otherwise demonstrates promise.</strong></p>',
    'format' => 'full_html',
  );
  $export['qr_85_criteria_1_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_85_criteria_1_desc_state';
  $strongarm->value = 'expanded';
  $export['qr_85_criteria_1_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_85_criteria_1_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_85_criteria_1_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_85_criteria_1_title';
  $strongarm->value = array(
    'value' => '<p>1. Reflects research and/or the principles of effective professional learning</p>',
    'format' => 'full_html',
  );
  $export['qr_85_criteria_1_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_85_criteria_2_description';
  $strongarm->value = array(
    'value' => '<p style="font-family: Arial, \'Helvetica sans-serif\';"><strong>• Clarify Intended Learning</strong></p><p style="font-family: Arial, \'Helvetica sans-serif\';">o The resource clearly articulates learning targets that reflect the Common Core State Standards.</p><p style="font-family: Arial, \'Helvetica sans-serif\';">o The resource clearly articulates success criteria.</p><p style="font-family: Arial, \'Helvetica sans-serif\';">o The resource is designed coherently, so that all content aligns to learning goals and success criteria.</p><p style="font-family: Arial, \'Helvetica sans-serif\';"><strong>• Elicit Evidence</strong></p><p style="font-family: Arial, \'Helvetica sans-serif\';">o The resource includes tasks and/or strategies to elicit evidence of learning (e.g., self-assessments, self-reflection, educator-directed).&nbsp;</p><p style="font-family: Arial, \'Helvetica sans-serif\';"><strong>• Interpret Evidence</strong></p><p style="font-family: Arial, \'Helvetica sans-serif\';">o The resource provides a way (e.g. method, model, process) to analyze or interpret evidence.</p><p style="font-family: Arial, \'Helvetica sans-serif\';"><strong>• Act on Evidence</strong></p><p style="font-family: Arial, \'Helvetica sans-serif\';">o The resource provides opportunities or recommendations for responsive action to evidence (e.g. provide feedback to participants, suggest grouping of participants, create action plans, set goals, revise learning experience based on analysis of evidence).</p><p style="font-family: Arial, \'Helvetica sans-serif\';"><strong>• The resource enables students to actively engage in the assessment and learning process.&nbsp;</strong></p>',
    'format' => 'full_html',
  );
  $export['qr_85_criteria_2_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_85_criteria_2_desc_state';
  $strongarm->value = 'expanded';
  $export['qr_85_criteria_2_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_85_criteria_2_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_85_criteria_2_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_85_criteria_2_title';
  $strongarm->value = array(
    'value' => '<p>2. Incorporates high-quality formative assessment practices</p>',
    'format' => 'full_html',
  );
  $export['qr_85_criteria_2_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_85_criteria_3_description';
  $strongarm->value = array(
    'value' => '<p><strong>• The resource reflects one or more principles of Universal Design for Learning (e.g., multiple means of representation, action and expression, engagement).</strong></p><p><strong>• The resource is accessible to, or can be modified for, a range of educators, including educators with disabilities and culturally diverse educators.</strong></p><p><strong>• The resource supports a range of learners. It can be differentiated based on educator readiness, interest, or learning style.</strong></p><p><strong>• The resource provides supplemental materials and strategies for educators who would like more or less support in the specific topic or content.</strong></p><p><strong>• The resource can be used and/or adapted in multiple teaching and school contexts.</strong></p><p><strong>• The resource reflects diversity in the educators and students it profiles.</strong></p><p><strong>• The resource can be easily adapted for a variety of formats (e.g., PLCs/collaborative learning teams, individuals, online learning).</strong></p>',
    'format' => 'full_html',
  );
  $export['qr_85_criteria_3_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_85_criteria_3_desc_state';
  $strongarm->value = 'expanded';
  $export['qr_85_criteria_3_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_85_criteria_3_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_85_criteria_3_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_85_criteria_3_title';
  $strongarm->value = array(
    'value' => '<p>3. Reflects learner differences and supports personalized learning</p>',
    'format' => 'full_html',
  );
  $export['qr_85_criteria_3_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_85_criteria_4_description';
  $strongarm->value = array(
    'value' => '<p><strong>• The resource is self-explanatory or easy to use.</strong></p><p><strong>• The resource engages the educator through stimulating and challenging content, and/or creative, inventive formats.</strong></p>',
    'format' => 'full_html',
  );
  $export['qr_85_criteria_4_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_85_criteria_4_desc_state';
  $strongarm->value = 'expanded';
  $export['qr_85_criteria_4_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_85_criteria_4_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_85_criteria_4_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_85_criteria_4_title';
  $strongarm->value = array(
    'value' => '<p>4.&nbsp;Demonstrates utility, engagement, and user-friendliness</p>',
    'format' => 'full_html',
  );
  $export['qr_85_criteria_4_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_85_criteria_5_description';
  $strongarm->value = array(
    'value' => '<p><strong>• The resource integrates technology in a way that increases the educator’s understanding and teaching of the Common Core State Standards.</strong></p><p><strong>• The technology/media support the educator in one or more steps of the formative assessment process (i.e., Clarify Intended Learning, Elicit Evidence, Interpret Evidence, Act on Evidence).</strong></p><p><strong>• The technology and media are accessible by a range of educators.</strong></p>',
    'format' => 'full_html',
  );
  $export['qr_85_criteria_5_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_85_criteria_5_desc_state';
  $strongarm->value = 'collapsed';
  $export['qr_85_criteria_5_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_85_criteria_5_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_85_criteria_5_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_85_criteria_5_title';
  $strongarm->value = array(
    'value' => '<p>5. Integrates media and technology effectively</p>',
    'format' => 'full_html',
  );
  $export['qr_85_criteria_5_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_85_criteria_num';
  $strongarm->value = '5';
  $export['qr_85_criteria_num'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_85_help';
  $strongarm->value = array(
    'value' => '<p>If you are unable to complete the review in the timeframe, click “Cancel Review” and the resource will be returned to the queue. If you are in the midst of a review and the 72-hour window is reached, the resource will be returned to the queue. Finally, if you are in the midst of a review and need to step away from the computer, you may save your review for later (as long as the 72-hour window is not reached). For additional assistance, refer to the Help section.</p>',
    'format' => 'full_html',
  );
  $export['qr_85_help'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_10_description';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_10_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_10_desc_state';
  $strongarm->value = 'collapsed';
  $export['qr_86_criteria_10_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_10_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_10_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_10_title';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_10_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_11_description';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_11_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_11_desc_state';
  $strongarm->value = 'collapsed';
  $export['qr_86_criteria_11_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_11_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_11_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_11_title';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_11_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_1_description';
  $strongarm->value = array(
    'value' => '<p>Professional Learning and Instructional Resource Set 1 Description</p>',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_1_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_1_desc_state';
  $strongarm->value = 'collapsed';
  $export['qr_86_criteria_1_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_1_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '<p>Professional Learning and Instructional Resource Set 1 Radio</p>',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_1_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_1_title';
  $strongarm->value = array(
    'value' => '<p>Professional Learning and Instructional Resource Set 1 Title</p>',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_1_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_2_description';
  $strongarm->value = array(
    'value' => '<p>Professional Learning and Instructional Resource Set 2 Desc</p>',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_2_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_2_desc_state';
  $strongarm->value = 'collapsed';
  $export['qr_86_criteria_2_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_2_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '<p>Professional Learning and Instructional Resource Set 2 Radio</p>',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_2_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_2_title';
  $strongarm->value = array(
    'value' => '<p>Professional Learning and Instructional Resource Set 2 Title</p>',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_2_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_3_description';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_3_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_3_desc_state';
  $strongarm->value = 'collapsed';
  $export['qr_86_criteria_3_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_3_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_3_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_3_title';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_3_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_4_description';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_4_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_4_desc_state';
  $strongarm->value = 'collapsed';
  $export['qr_86_criteria_4_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_4_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_4_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_4_title';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_4_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_5_description';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_5_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_5_desc_state';
  $strongarm->value = 'collapsed';
  $export['qr_86_criteria_5_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_5_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_5_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_5_title';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_5_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_6_description';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_6_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_6_desc_state';
  $strongarm->value = 'collapsed';
  $export['qr_86_criteria_6_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_6_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_6_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_6_title';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_6_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_7_description';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_7_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_7_desc_state';
  $strongarm->value = 'collapsed';
  $export['qr_86_criteria_7_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_7_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_7_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_7_title';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_7_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_8_description';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_8_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_8_desc_state';
  $strongarm->value = 'collapsed';
  $export['qr_86_criteria_8_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_8_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_8_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_8_title';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_8_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_9_description';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_9_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_9_desc_state';
  $strongarm->value = 'collapsed';
  $export['qr_86_criteria_9_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_9_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_9_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_9_title';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_86_criteria_9_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_criteria_num';
  $strongarm->value = '11';
  $export['qr_86_criteria_num'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_86_help';
  $strongarm->value = array(
    'value' => '<p>Professional Learning and Instructional Resource Helpful Information&nbsp;Lorem ipsum dolor sit amet, ut qui affert everti blandit, eu tation numquam eum, nisl oportere volutpat eu sit. Singulis disputationi vel te. Mea nominati repudiare ea, ex cum omittam aliquando disputando. Ex sit audire dissentias, ad duo quem vocent. Cum eu autem necessitatibus, purto vivendo eu qui.</p>',
    'format' => 'full_html',
  );
  $export['qr_86_help'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_level_1';
  $strongarm->value = array(
    'value' => '<p>No Evidence</p>',
    'format' => 'full_html',
  );
  $export['qr_level_1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_level_2';
  $strongarm->value = array(
    'value' => '<p>Minimal Evidence</p>',
    'format' => 'full_html',
  );
  $export['qr_level_2'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_level_3';
  $strongarm->value = array(
    'value' => '<p>Partial Evidence</p>',
    'format' => 'full_html',
  );
  $export['qr_level_3'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_level_4';
  $strongarm->value = array(
    'value' => '<p>Adequate Evidence</p>',
    'format' => 'full_html',
  );
  $export['qr_level_4'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_level_5';
  $strongarm->value = array(
    'value' => '<p>Exemplary Evidence</p>',
    'format' => 'full_html',
  );
  $export['qr_level_5'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_rec_0';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_rec_0'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_rec_1';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_rec_1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_rec_2';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_rec_2'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'qr_rec_3';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['qr_rec_3'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_1_description';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['resource_gate_keeper_criteria_1_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_1_desc_state';
  $strongarm->value = 'expanded';
  $export['resource_gate_keeper_criteria_1_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_1_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '<p><span style="color: #000000; font-family: \'Lucida Grande\', \'Lucida Sans Unicode\', sans-serif; font-size: 13px; line-height: 20px;">&nbsp;</span></p>',
    'format' => 'full_html',
  );
  $export['resource_gate_keeper_criteria_1_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_1_title';
  $strongarm->value = array(
    'value' => '<p>Does the information in the Cover Profile accurately match the resource?</p>',
    'format' => 'full_html',
  );
  $export['resource_gate_keeper_criteria_1_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_2_description';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['resource_gate_keeper_criteria_2_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_2_desc_state';
  $strongarm->value = 'expanded';
  $export['resource_gate_keeper_criteria_2_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_2_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '<p><span style="color: #000000; font-family: \'Lucida Grande\', \'Lucida Sans Unicode\', sans-serif; font-size: 13px; line-height: 20px;">&nbsp;</span></p>',
    'format' => 'full_html',
  );
  $export['resource_gate_keeper_criteria_2_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_2_title';
  $strongarm->value = array(
    'value' => '<p><!--[if gte mso 9]><xml>
 <o:DocumentProperties>
  <o:Revision>0</o:Revision>
  <o:TotalTime>0</o:TotalTime>
  <o:Pages>1</o:Pages>
  <o:Words>14</o:Words>
  <o:Characters>80</o:Characters>
  <o:Company>Wireless Generation Inc</o:Company>
  <o:Lines>1</o:Lines>
  <o:Paragraphs>1</o:Paragraphs>
  <o:CharactersWithSpaces>93</o:CharactersWithSpaces>
  <o:Version>14.0</o:Version>
 </o:DocumentProperties>
 <o:OfficeDocumentSettings>
  <o:RelyOnVML/>
  <o:AllowPNG/>
 </o:OfficeDocumentSettings>
</xml><![endif]--> <!--[if gte mso 9]><xml>
 <w:WordDocument>
  <w:View>Normal</w:View>
  <w:Zoom>0</w:Zoom>
  <w:TrackMoves/>
  <w:TrackFormatting/>
  <w:PunctuationKerning/>
  <w:ValidateAgainstSchemas/>
  <w:SaveIfXMLInvalid>false</w:SaveIfXMLInvalid>
  <w:IgnoreMixedContent>false</w:IgnoreMixedContent>
  <w:AlwaysShowPlaceholderText>false</w:AlwaysShowPlaceholderText>
  <w:DoNotPromoteQF/>
  <w:LidThemeOther>EN-US</w:LidThemeOther>
  <w:LidThemeAsian>JA</w:LidThemeAsian>
  <w:LidThemeComplexScript>X-NONE</w:LidThemeComplexScript>
  <w:Compatibility>
   <w:BreakWrappedTables/>
   <w:SnapToGridInCell/>
   <w:WrapTextWithPunct/>
   <w:UseAsianBreakRules/>
   <w:DontGrowAutofit/>
   <w:SplitPgBreakAndParaMark/>
   <w:EnableOpenTypeKerning/>
   <w:DontFlipMirrorIndents/>
   <w:OverrideTableStyleHps/>
  </w:Compatibility>
  <m:mathPr>
   <m:mathFont m:val="Cambria Math"/>
   <m:brkBin m:val="before"/>
   <m:brkBinSub m:val="&#45;-"/>
   <m:smallFrac m:val="off"/>
   <m:dispDef/>
   <m:lMargin m:val="0"/>
   <m:rMargin m:val="0"/>
   <m:defJc m:val="centerGroup"/>
   <m:wrapIndent m:val="1440"/>
   <m:intLim m:val="subSup"/>
   <m:naryLim m:val="undOvr"/>
  </m:mathPr></w:WordDocument>
</xml><![endif]--><!--[if gte mso 9]><xml>
 <w:LatentStyles DefLockedState="false" DefUnhideWhenUsed="true"
  DefSemiHidden="true" DefQFormat="false" DefPriority="99"
  LatentStyleCount="276">
  <w:LsdException Locked="false" Priority="0" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Normal"/>
  <w:LsdException Locked="false" Priority="9" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="heading 1"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 2"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 3"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 4"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 5"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 6"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 7"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 8"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 9"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 1"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 2"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 3"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 4"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 5"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 6"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 7"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 8"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 9"/>
  <w:LsdException Locked="false" Priority="35" QFormat="true" Name="caption"/>
  <w:LsdException Locked="false" Priority="10" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Title"/>
  <w:LsdException Locked="false" Priority="1" Name="Default Paragraph Font"/>
  <w:LsdException Locked="false" Priority="11" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Subtitle"/>
  <w:LsdException Locked="false" Priority="22" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Strong"/>
  <w:LsdException Locked="false" Priority="20" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Emphasis"/>
  <w:LsdException Locked="false" Priority="59" SemiHidden="false"
   UnhideWhenUsed="false" Name="Table Grid"/>
  <w:LsdException Locked="false" UnhideWhenUsed="false" Name="Placeholder Text"/>
  <w:LsdException Locked="false" Priority="1" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="No Spacing"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 1"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 1"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 1"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 1"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 1"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 1"/>
  <w:LsdException Locked="false" UnhideWhenUsed="false" Name="Revision"/>
  <w:LsdException Locked="false" Priority="34" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="List Paragraph"/>
  <w:LsdException Locked="false" Priority="29" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Quote"/>
  <w:LsdException Locked="false" Priority="30" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Intense Quote"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 1"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 1"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 1"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 1"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 1"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 1"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 1"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 1"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 2"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 2"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 2"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 2"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 2"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 2"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 2"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 2"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 2"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 2"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 2"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 2"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 2"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 2"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 3"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 3"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 3"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 3"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 3"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 3"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 3"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 3"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 3"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 3"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 3"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 3"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 3"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 3"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 4"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 4"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 4"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 4"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 4"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 4"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 4"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 4"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 4"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 4"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 4"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 4"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 4"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 4"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 5"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 5"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 5"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 5"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 5"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 5"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 5"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 5"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 5"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 5"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 5"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 5"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 5"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 5"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 6"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 6"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 6"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 6"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 6"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 6"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 6"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 6"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 6"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 6"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 6"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 6"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 6"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 6"/>
  <w:LsdException Locked="false" Priority="19" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Subtle Emphasis"/>
  <w:LsdException Locked="false" Priority="21" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Intense Emphasis"/>
  <w:LsdException Locked="false" Priority="31" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Subtle Reference"/>
  <w:LsdException Locked="false" Priority="32" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Intense Reference"/>
  <w:LsdException Locked="false" Priority="33" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Book Title"/>
  <w:LsdException Locked="false" Priority="37" Name="Bibliography"/>
  <w:LsdException Locked="false" Priority="39" QFormat="true" Name="TOC Heading"/>
 </w:LatentStyles>
</xml><![endif]--> <!--[if gte mso 10]>
<style>
 /* Style Definitions */
table.MsoNormalTable
	{mso-style-name:"Table Normal";
	mso-tstyle-rowband-size:0;
	mso-tstyle-colband-size:0;
	mso-style-noshow:yes;
	mso-style-priority:99;
	mso-style-parent:"";
	mso-padding-alt:0in 5.4pt 0in 5.4pt;
	mso-para-margin:0in;
	mso-para-margin-bottom:.0001pt;
	mso-pagination:widow-orphan;
	font-size:10.0pt;
	font-family:Calibri;}
</style>
<![endif]--> <!--StartFragment-->Is the resource legible, viewable, and does the technology function properly (if applicable)?</p>',
    'format' => 'full_html',
  );
  $export['resource_gate_keeper_criteria_2_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_3_description';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['resource_gate_keeper_criteria_3_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_3_desc_state';
  $strongarm->value = 'expanded';
  $export['resource_gate_keeper_criteria_3_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_3_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['resource_gate_keeper_criteria_3_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_3_title';
  $strongarm->value = array(
    'value' => '<p><!--[if gte mso 9]><xml>
 <o:DocumentProperties>
  <o:Revision>0</o:Revision>
  <o:TotalTime>0</o:TotalTime>
  <o:Pages>1</o:Pages>
  <o:Words>4</o:Words>
  <o:Characters>28</o:Characters>
  <o:Company>Wireless Generation Inc</o:Company>
  <o:Lines>1</o:Lines>
  <o:Paragraphs>1</o:Paragraphs>
  <o:CharactersWithSpaces>31</o:CharactersWithSpaces>
  <o:Version>14.0</o:Version>
 </o:DocumentProperties>
 <o:OfficeDocumentSettings>
  <o:RelyOnVML/>
  <o:AllowPNG/>
 </o:OfficeDocumentSettings>
</xml><![endif]--> <!--[if gte mso 9]><xml>
 <w:WordDocument>
  <w:View>Normal</w:View>
  <w:Zoom>0</w:Zoom>
  <w:TrackMoves/>
  <w:TrackFormatting/>
  <w:PunctuationKerning/>
  <w:ValidateAgainstSchemas/>
  <w:SaveIfXMLInvalid>false</w:SaveIfXMLInvalid>
  <w:IgnoreMixedContent>false</w:IgnoreMixedContent>
  <w:AlwaysShowPlaceholderText>false</w:AlwaysShowPlaceholderText>
  <w:DoNotPromoteQF/>
  <w:LidThemeOther>EN-US</w:LidThemeOther>
  <w:LidThemeAsian>JA</w:LidThemeAsian>
  <w:LidThemeComplexScript>X-NONE</w:LidThemeComplexScript>
  <w:Compatibility>
   <w:BreakWrappedTables/>
   <w:SnapToGridInCell/>
   <w:WrapTextWithPunct/>
   <w:UseAsianBreakRules/>
   <w:DontGrowAutofit/>
   <w:SplitPgBreakAndParaMark/>
   <w:EnableOpenTypeKerning/>
   <w:DontFlipMirrorIndents/>
   <w:OverrideTableStyleHps/>
  </w:Compatibility>
  <m:mathPr>
   <m:mathFont m:val="Cambria Math"/>
   <m:brkBin m:val="before"/>
   <m:brkBinSub m:val="&#45;-"/>
   <m:smallFrac m:val="off"/>
   <m:dispDef/>
   <m:lMargin m:val="0"/>
   <m:rMargin m:val="0"/>
   <m:defJc m:val="centerGroup"/>
   <m:wrapIndent m:val="1440"/>
   <m:intLim m:val="subSup"/>
   <m:naryLim m:val="undOvr"/>
  </m:mathPr></w:WordDocument>
</xml><![endif]--><!--[if gte mso 9]><xml>
 <w:LatentStyles DefLockedState="false" DefUnhideWhenUsed="true"
  DefSemiHidden="true" DefQFormat="false" DefPriority="99"
  LatentStyleCount="276">
  <w:LsdException Locked="false" Priority="0" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Normal"/>
  <w:LsdException Locked="false" Priority="9" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="heading 1"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 2"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 3"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 4"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 5"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 6"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 7"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 8"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 9"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 1"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 2"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 3"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 4"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 5"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 6"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 7"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 8"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 9"/>
  <w:LsdException Locked="false" Priority="35" QFormat="true" Name="caption"/>
  <w:LsdException Locked="false" Priority="10" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Title"/>
  <w:LsdException Locked="false" Priority="1" Name="Default Paragraph Font"/>
  <w:LsdException Locked="false" Priority="11" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Subtitle"/>
  <w:LsdException Locked="false" Priority="22" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Strong"/>
  <w:LsdException Locked="false" Priority="20" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Emphasis"/>
  <w:LsdException Locked="false" Priority="59" SemiHidden="false"
   UnhideWhenUsed="false" Name="Table Grid"/>
  <w:LsdException Locked="false" UnhideWhenUsed="false" Name="Placeholder Text"/>
  <w:LsdException Locked="false" Priority="1" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="No Spacing"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 1"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 1"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 1"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 1"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 1"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 1"/>
  <w:LsdException Locked="false" UnhideWhenUsed="false" Name="Revision"/>
  <w:LsdException Locked="false" Priority="34" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="List Paragraph"/>
  <w:LsdException Locked="false" Priority="29" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Quote"/>
  <w:LsdException Locked="false" Priority="30" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Intense Quote"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 1"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 1"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 1"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 1"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 1"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 1"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 1"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 1"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 2"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 2"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 2"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 2"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 2"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 2"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 2"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 2"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 2"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 2"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 2"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 2"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 2"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 2"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 3"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 3"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 3"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 3"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 3"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 3"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 3"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 3"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 3"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 3"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 3"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 3"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 3"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 3"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 4"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 4"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 4"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 4"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 4"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 4"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 4"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 4"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 4"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 4"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 4"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 4"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 4"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 4"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 5"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 5"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 5"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 5"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 5"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 5"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 5"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 5"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 5"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 5"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 5"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 5"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 5"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 5"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 6"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 6"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 6"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 6"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 6"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 6"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 6"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 6"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 6"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 6"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 6"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 6"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 6"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 6"/>
  <w:LsdException Locked="false" Priority="19" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Subtle Emphasis"/>
  <w:LsdException Locked="false" Priority="21" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Intense Emphasis"/>
  <w:LsdException Locked="false" Priority="31" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Subtle Reference"/>
  <w:LsdException Locked="false" Priority="32" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Intense Reference"/>
  <w:LsdException Locked="false" Priority="33" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Book Title"/>
  <w:LsdException Locked="false" Priority="37" Name="Bibliography"/>
  <w:LsdException Locked="false" Priority="39" QFormat="true" Name="TOC Heading"/>
 </w:LatentStyles>
</xml><![endif]--> <!--[if gte mso 10]>
<style>
 /* Style Definitions */
table.MsoNormalTable
	{mso-style-name:"Table Normal";
	mso-tstyle-rowband-size:0;
	mso-tstyle-colband-size:0;
	mso-style-noshow:yes;
	mso-style-priority:99;
	mso-style-parent:"";
	mso-padding-alt:0in 5.4pt 0in 5.4pt;
	mso-para-margin:0in;
	mso-para-margin-bottom:.0001pt;
	mso-pagination:widow-orphan;
	font-size:10.0pt;
	font-family:Calibri;}
</style>
<![endif]--> <!--StartFragment-->Is the resource comprehensible?<!--EndFragment--></p>',
    'format' => 'full_html',
  );
  $export['resource_gate_keeper_criteria_3_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_4_description';
  $strongarm->value = array(
    'value' => '<p><span style="font-size: 9px; line-height: 14px;">&nbsp;</span>Clarify Intended Learning /&nbsp;Elicit Evidence / &nbsp;Interpret Evidence /&nbsp;Act on Evidence</p>',
    'format' => 'full_html',
  );
  $export['resource_gate_keeper_criteria_4_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_4_desc_state';
  $strongarm->value = 'expanded';
  $export['resource_gate_keeper_criteria_4_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_4_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['resource_gate_keeper_criteria_4_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_4_title';
  $strongarm->value = array(
    'value' => '<p>Does the resource support educators and/or students in using at least one of the following attributes of the formative assessment process to implement the Common Core State Standards?</p>',
    'format' => 'full_html',
  );
  $export['resource_gate_keeper_criteria_4_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_5_description';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['resource_gate_keeper_criteria_5_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_5_desc_state';
  $strongarm->value = 'expanded';
  $export['resource_gate_keeper_criteria_5_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_5_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['resource_gate_keeper_criteria_5_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_5_title';
  $strongarm->value = array(
    'value' => '<p>Is the resource free from bias and objectionable or culturally insensitive material (e.g., related to race, culture, religion, political viewpoint, gender, or socioeconomic status)?</p>',
    'format' => 'full_html',
  );
  $export['resource_gate_keeper_criteria_5_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_6_description';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['resource_gate_keeper_criteria_6_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_6_desc_state';
  $strongarm->value = 'expanded';
  $export['resource_gate_keeper_criteria_6_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_6_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['resource_gate_keeper_criteria_6_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_6_title';
  $strongarm->value = array(
    'value' => '<p>Is the resource free of student records and other information that may allow a user to identify a specific student?</p>',
    'format' => 'full_html',
  );
  $export['resource_gate_keeper_criteria_6_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_7_description';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['resource_gate_keeper_criteria_7_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_7_desc_state';
  $strongarm->value = 'expanded';
  $export['resource_gate_keeper_criteria_7_desc_state'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_7_radiobuttonshelptext';
  $strongarm->value = array(
    'value' => '',
    'format' => 'full_html',
  );
  $export['resource_gate_keeper_criteria_7_radiobuttonshelptext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_7_title';
  $strongarm->value = array(
    'value' => '<p>Is the resource available free of charge, for the duration of its use?</p>',
    'format' => 'full_html',
  );
  $export['resource_gate_keeper_criteria_7_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_criteria_num';
  $strongarm->value = '7';
  $export['resource_gate_keeper_criteria_num'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_help';
  $strongarm->value = array(
    'value' => '<p style="font-family: Arial, Helvetica, sans-serif;">This resource is ready for review. &nbsp; Please review the&nbsp;<strong><a href="/system/files/resource/gatekeeping-guide_20140303_1.docx" target="_blank">Gate-Keeping Guide</a></strong>&nbsp;for information on how to complete this step.</p><p style="font-family: Arial, Helvetica, sans-serif;">As the first reviewer, you are responsible for determining whether it meets the Gate-Keeping Criteria.To begin the process, click the “Start Review” button. You have 72 hours to complete this step. &nbsp;At any point during this window, you can click the “Save and Close” button to save your work and return later to complete it. &nbsp;If you are unable to finish the review within 72 hours, click “Cancel Review” and the resource will be returned to the queue.&nbsp;</p><p style="font-family: Arial, Helvetica, sans-serif;">For additional assistance, visit the&nbsp;<strong><a href="https://beta.smarterbalancedlibrary.org/help-topics" target="_blank">Help Topics</a></strong>.</p>',
    'format' => 'full_html',
  );
  $export['resource_gate_keeper_help'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_gate_keeper_intro';
  $strongarm->value = array(
    'value' => '<p style="font-family: Arial, Helvetica, sans-serif;">This resource is ready for review. &nbsp; Please review the&nbsp;<strong><a href="/system/files/resource/gatekeeping-guide_20140303_1.docx" target="_blank">Gate-Keeping Guide</a></strong> for information on how to complete this step.</p><p style="font-family: Arial, Helvetica, sans-serif;">As the first reviewer, you are responsible for determining whether it meets the Gate-Keeping Criteria.To begin the process, click the “Start Review” button. You have 72 hours to complete this step. &nbsp;At any point during this window, you can click the “Save and Close” button to save your work and return later to complete it. &nbsp;If you are unable to finish the review within 72 hours, click “Cancel Review” and the resource will be returned to the queue.&nbsp;</p><p style="font-family: Arial, Helvetica, sans-serif;">For additional assistance, visit the <strong><a href="https://beta.smarterbalancedlibrary.org/help-topics" target="_blank">Help Topics</a></strong>.</p>',
    'format' => 'full_html',
  );
  $export['resource_gate_keeper_intro'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_post_help';
  $strongarm->value = array(
    'value' => '<p>Three reviewers have reviewed this resource. &nbsp;Their posting decisions were substantially different, meriting an SLT arbitration. &nbsp;Below you will find information about each reviewer, his/her recommendation, the rationale for his/her recommendation, and his/her comments listed criterion-by-criterion.&nbsp;</p>',
    'format' => 'full_html',
  );
  $export['resource_post_help'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_post_intro';
  $strongarm->value = array(
    'value' => '<p>This resource is ready for review. To start its review, click the “Start Review” button. “You have 72 hours to complete this step. &nbsp;At any point during this window, you can click the “Save and Close” button to save your work and return later to complete it. &nbsp;If you are unable to finish the review within 72 hours, click “Cancel Review” and the resource will be returned to the queue.&nbsp;</p><p>For additional assistance, visit the Help section.</p>',
    'format' => 'full_html',
  );
  $export['resource_post_intro'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'resource_review_intro';
  $strongarm->value = array(
    'value' => '<p>This resource is ready for a Quality Criteria review. Please review the <a href="/system/files/resource/quality-criteria-guide_20140303.docx" target="_blank"><strong>Quality Criteria Guide</strong></a><strong>&nbsp;</strong>for more information on how to complete this step.</p><p>At any point during the 72-hour window allocated to this step you can click the “Save and Close” button to save your work and return later to complete it. &nbsp;If you are unable to finish the review within 72 hours, click “Cancel Review” and the resource will be returned to the queue.&nbsp;</p><p>For additional assistance, visit the <strong><a href="https://beta.smarterbalancedlibrary.org/help-topics" target="_blank">Help Topics</a></strong>.</p>',
    'format' => 'full_html',
  );
  $export['resource_review_intro'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'sbac_resource_advanced_guide';
  $strongarm->value = '';
  $export['sbac_resource_advanced_guide'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'sbac_resource_general_guide';
  $strongarm->value = '<p class="MsoNormal" style="margin-bottom: 15.0pt;"><span style="font-size: 9pt; font-family: Arial, sans-serif;">You’re about to create a resource.&nbsp; Please review the&nbsp;<a href="/sites/all/themes/custom/sbac/workflow_resources/Cover_Profile_Guide_Playlists_June2016.pdf" target="_blank"><strong>Cover Profile Guide</strong></a>&nbsp;for more information on how to begin this process.</span></p><p class="MsoNormal" style="margin-bottom: 15.0pt;"><span style="font-size: 9pt; font-family: Arial, sans-serif;">Here\'s a helpful <strong><a href="/sites/all/themes/custom/sbac/workflow_resources/resource_recording%20templat.docx" target="_blank">Template</a></strong> to use when creating your resource, for planning and recording the information that will be included.</span></p><p style="margin-top: 0in; margin-right: 0in; margin-bottom: 15.0pt; margin-left: 0in;"><span style="font-size: 9pt; font-family: Arial, sans-serif;">The Digital Library will walk you through four (4) tabs of required information.&nbsp; Be sure to complete all required fields and avoid using any inappropriate language. &nbsp;Should you miss a field and/or include inappropriate language, an error message will appear and request that you make adjustments. &nbsp;If you have any further questions, please&nbsp;visit the <strong><a href="https://beta.smarterbalancedlibrary.org/help-topics" target="_blank">Help Topics</a></strong> section.</span></p>';
  $export['sbac_resource_general_guide'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'sbac_resource_materials_guide';
  $strongarm->value = '<p class="MsoNormal playlist-template" style="margin-bottom: 15.0pt;"><span style="font-size: 9pt; font-family: Arial, sans-serif;">If creating a Playlist, please refer to the <strong><a href="/sites/all/themes/custom/SBAC/workflow_resources/Educator_Learning_Guide_and_Digital_Library_Resource_Playlist_Template_June2016_v4.docm">Playlist Template</a></strong> for an example.</span></p><p class="MsoNormal" style="margin-bottom: 15.0pt;"><span style="font-size: 9pt; font-family: Arial, sans-serif;">Review the&nbsp;</span><strong style="font-family: Arial, sans-serif; font-size: 9pt; line-height: 1.2;"><a href="/sites/all/themes/custom/SBAC/workflow_resources/Cover_Profile_Guide_Playlists_June2016.pdf" target="_blank">Cover Profile Guide</a></strong><span style="font-size: 9pt; font-family: Arial, sans-serif;">&nbsp;and the </span><strong style="font-family: Arial, sans-serif; font-size: 9pt; line-height: 1.2;"><a href="/system/files/resource/links_101_final.pdf" target="_blank">Links 101 Guide</a>&nbsp;</strong><span style="font-size: 9pt; font-family: Arial, sans-serif;">for detailed instructions on how to</span></p><ul><li><span style="font-size: 9pt; font-family: Arial, sans-serif;" data-mce-mark="1">identify the license for your materials</span></li><li><span style="font-size: 9pt; font-family: Arial, sans-serif;" data-mce-mark="1">upload, imbed, or link materials for your resource</span></li></ul><p><span style="font-size: 9pt; font-family: Arial, sans-serif;" data-mce-mark="1">Before you upload materials to the Digital Library, you must determine their copyright.&nbsp; You do not need to get copyright permission for materials that: 1) are public domain; 2) require only that you credit the owner; or 3) are sourced from organizations with which Smarter Balanced has agreements (see below for information on these agreements). You must obtain copyright permission for all other materials. See pages 9-14 in the Cover Profile Guide for more information on copyrights.&nbsp;</span></p><p><span style="font-size: 9pt; font-family: Arial, sans-serif;" data-mce-mark="1">To request permission to use copyrighted materials, complete the highlighted sections of the <strong><a href="/system/files/suggested_text_for_email_to_ask_for_copyright_permission_20150520.docx" target="_blank">Suggested Email</a></strong>,&nbsp;</span><span style="font-size: 9pt; font-family: Arial, sans-serif;" data-mce-mark="1">then copy and paste the text into an email to the owner. Download the&nbsp;</span><a href="/system/files/help_page/digital_library_copyright_clearance_form_2015_06_16.docx" target="_blank"><strong style="line-height: 1;"><span style="font-size: 9pt; font-family: Arial, sans-serif;" data-mce-mark="1">Copyright Permission Form </span></strong></a><span style="font-size: 9pt; font-family: Arial, sans-serif;" data-mce-mark="1">and the <a href="/system/files/digital_library_factsheet_01-21-2015.pdf" target="_blank"><strong>Digital Library Factsheet</strong></a>, complete the table at the top of the clearance form, and attach both documents&nbsp;to the email.</span></p><p><span style="font-size: 9pt; font-family: Arial, sans-serif;" data-mce-mark="1">Smarter Balanced has agreements with two organizations,<span style="font-size: 9pt; font-family: Arial, sans-serif;" data-mce-mark="1">&nbsp;</span><strong style="line-height: 1.2; font-size: 9pt;"><a href="/system/files/resource/2._20140219_external_material_form_-_mars.docx" target="_blank">Mathematics Assessment Resource Service (MARS)</a></strong>&nbsp;and&nbsp;<strong style="line-height: 1.2; font-size: 9pt;"><a href="/system/files/resource/20140219_external_material_form_-_teaching_channel.docx" target="_blank">Teaching Channel</a></strong>, to link directly&nbsp;</span><span style="font-size: 9pt; font-family: Arial, sans-serif;" data-mce-mark="1">to their materials without obtaining permission each time.&nbsp;</span><span style="font-size: 9pt; font-family: Arial, sans-serif;" data-mce-mark="1">Acess the <strong>External Material Form</strong> to submit resources from these sources by clicking on the appropriate MARS or Teaching Channel link in the previous sentence.</span></p><p><span style="font-size: 9pt; font-family: Arial, sans-serif;" data-mce-mark="1">After you have identified the license and obtained permission from the owner (where applicable), you are ready to upload materials.</span></p><p><span style="font-size: 9pt; font-family: Arial, sans-serif;" data-mce-mark="1"><span style="font-size: 9pt; font-family: Arial, sans-serif;" data-mce-mark="1">First, upload a resource card image. Digital Library users will see this image when browsing in the library, so choose something that accurately represents the materials. Then, upload the set of files and/or video links that make up the resource. Use the tools below to identify primary and secondary files, rearrange the order of files, or delete files.&nbsp; Additional information about uploading materials is available in the&nbsp;<strong style="line-height: 14.3999996185303px; font-family: Arial, sans-serif; font-size: 12px;"><a href="https://beta.smarterbalancedlibrary.org/help-topics" target="_blank">Help Topics</a>&nbsp;</strong><span style="font-size: 9pt; font-family: Arial, sans-serif;" data-mce-mark="1">section</span>&nbsp;of the Digital Library.</span></span></p>';
  $export['sbac_resource_materials_guide'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'sbac_resource_summary_guide';
  $strongarm->value = '<p class="MsoNormal" style="margin-bottom: 15.0pt;"><span style="font-size: 9pt; font-family: Arial, sans-serif;">Now that you’ve uploaded your files, your next step is to provide descriptive information about the resource.&nbsp; Review the&nbsp;<strong><a href="/sites/all/themes/custom/SBAC/workflow_resources/Cover_Profile_Guide_Playlists_June2016.pdf" target="_blank">Cover Profile Guide</a>&nbsp;</strong>for information on how to complete this step.</span></p><p class="MsoNormal" style="margin-bottom: 15.0pt;"><span style="font-size: 9pt; font-family: Arial, sans-serif;">Complete all required fields and avoid using any inappropriate language. &nbsp;Should you miss a required field and/or include inappropriate language, error messages will appear and request that you make adjustments. &nbsp;If you have any further questions, please&nbsp;visit the <strong><a href="https://beta.smarterbalancedlibrary.org/help-topics" target="_blank">Help Topics</a></strong> section.</span></p>';
  $export['sbac_resource_summary_guide'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'sbac_resource_tags_guide';
  $strongarm->value = '<p class="MsoNormal" style="margin-bottom: 15.0pt;"><span style="font-size: 9pt; font-family: Arial, sans-serif;">The final step before completing your submission is to include some useful tags. &nbsp;Please review the&nbsp;<strong><a href="/sites/all/themes/custom/SBAC/workflow_resources/Cover_Profile_Guide_Playlists_June2016.pdf" target="_blank">Cover Profile Guide</a>&nbsp;</strong>for more information on how to complete this step.</span></p><p class="MsoNormal" style="margin-bottom: 15.0pt;"><span style="font-size: 9pt; font-family: Arial, sans-serif;">Tags are a way to help (filter) search results and identify similar resources within the Digital Library. Fill out the sections below, as appropriate, in order to describe the attributes most closely associated with this resource. You may select as many as are applicable.</span></p><p style="font-family: Arial, Helvetica, sans-serif;">&nbsp;<span style="font-size: 9pt; font-family: Arial, sans-serif;">Be sure to fill out all required fields. Should you miss a field, an error messages will appear and request that you make adjustments. &nbsp;If you have any further questions, please&nbsp;visit the <strong><a href="https://beta.smarterbalancedlibrary.org/help-topics" target="_blank">Help Topics</a></strong> section.</span></p>';
  $export['sbac_resource_tags_guide'] = $strongarm;

  return $export;
}

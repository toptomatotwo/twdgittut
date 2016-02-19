<?php/** * @file * Default theme implementation to display a node. * * Available variables: * - $title: the (sanitized) title of the node. * - $content: An array of node items. Use render($content) to print them all, *   or print a subset such as render($content['field_example']). Use *   hide($content['field_example']) to temporarily suppress the printing of a *   given element. * - $user_picture: The node author's picture from user-picture.tpl.php. * - $date: Formatted creation date. Preprocess functions can reformat it by *   calling format_date() with the desired parameters on the $created variable. * - $name: Themed username of node author output from theme_username(). * - $node_url: Direct URL of the current node. * - $display_submitted: Whether submission information should be displayed. * - $submitted: Submission information created from $name and $date during *   template_preprocess_node(). * - $classes: String of classes that can be used to style contextually through *   CSS. It can be manipulated through the variable $classes_array from *   preprocess functions. The default values can be one or more of the *   following: *   - node: The current template type; for example, "theming hook". *   - node-[type]: The current node type. For example, if the node is a *     "Blog entry" it would result in "node-blog". Note that the machine *     name will often be in a short form of the human readable label. *   - node-teaser: Nodes in teaser form. *   - node-preview: Nodes in preview mode. *   The following are controlled through the node publishing options. *   - node-promoted: Nodes promoted to the front page. *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser *     listings. *   - node-unpublished: Unpublished nodes visible only to administrators. * - $title_prefix (array): An array containing additional output populated by *   modules, intended to be displayed in front of the main title tag that *   appears in the template. * - $title_suffix (array): An array containing additional output populated by *   modules, intended to be displayed after the main title tag that appears in *   the template. * * Other variables: * - $node: Full node object. Contains data that may not be safe. * - $type: Node type; for example, story, page, blog, etc. * - $comment_count: Number of comments attached to the node. * - $uid: User ID of the node author. * - $created: Time the node was published formatted in Unix timestamp. * - $classes_array: Array of html class attribute values. It is flattened *   into a string within the variable $classes. * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in *   teaser listings. * - $id: Position of the node. Increments each time it's output. * * Node status variables: * - $view_mode: View mode; for example, "full", "teaser". * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser'). * - $page: Flag for the full page state. * - $promote: Flag for front page promotion state. * - $sticky: Flags for sticky post setting. * - $status: Flag for published status. * - $comment: State of comment settings for the node. * - $readmore: Flags true if the teaser content of the node cannot hold the *   main body content. * - $is_front: Flags true when presented in the front page. * - $logged_in: Flags true when the current user is a logged-in member. * - $is_admin: Flags true when the current user is an administrator. * * Field variables: for each field instance attached to the node a corresponding * variable is defined; for example, $node->body becomes $body. When needing to * access a field's raw values, developers/themers are strongly encouraged to * use these variables. Otherwise they will have to explicitly specify the * desired field language; for example, $node->body['en'], thus overriding any * language negotiation rule that was previously applied. * * @see template_preprocess() * @see template_preprocess_node() * @see template_process() * * @ingroup themeable */$style = 'style_1';if(isset($content['field_portfolio_layout_mode'])){    $style = $content['field_portfolio_layout_mode']['#items'][0]['value'];}$multimedia = field_get_items('node', $node, 'field_portfolio_multimedia');?><?php if($style == 'style_1'):?>    <div id="node-<?php print $node->nid; ?>" class=" <?php print $classes; ?> clearfix"<?php print $attributes; ?>>        <div class="container-single">        <div class="w-container">            <div class="portfolio-tiitle"><?php print $title; ?></div>            <?php if(isset($content['field_portfolio_subtitle'])):?>                <div class="subtext-portfolio center"><?php print $content['field_portfolio_subtitle']['#items'][0]['value'];?></div>            <?php endif;?>            <div class="portfolio-line"></div>            <div class="w-row row">                <?php if(isset($content['field_portfolio_description'])):?>                    <div class="w-col w-col-4">                        <div class="small-tittle"><?php print $content['field_portfolio_description']['#title'];?></div>                        <p class="left"><?php print $content['field_portfolio_description']['#items'][0]['value'];?></p>                    </div>                <?php endif;?>                <?php if(isset($content['body'])):?>                    <div class="w-col w-col-4 column">                        <p class="left"><?php print $content['body']['#items'][0]['value'];?></p>                    </div>                <?php endif;?>                <div class="w-col w-col-4">                    <div class="small-tittle"><?php print t('project details');?></div>                    <?php if(isset($content['field_portfolio_website'][0])):                        $data = $content['field_portfolio_website']['#items'][0]['value'];                        $wid = $content['field_portfolio_website'][0]['entity']['field_collection_item'][$data];                        ?>                        <?php if(isset($wid['field_portfolio_website_title'])):?>                            <p class="left p-margin"><span class="darker"><?php print $wid['field_portfolio_website_title']['#title'];?><?php print t(':');?></span> <?php print $wid['field_portfolio_website_title']['#items'][0]['value'];?></p>                        <?php endif;?>                            <div class="portfolio-line details"></div>                                <p class="left p-margin"><span class="darker"><?php print t('Date:');?></span> <?php print format_date($node->created,'custom','j F, Y');?></p>                            <div class="portfolio-line details"></div>                        <?php if(isset($wid['field_portfolio_website_link'])):?>                        <p class="left p-margin"><span class="darker"><?php print $wid['field_portfolio_website_link']['#title'];?><?php print t(':');?></span> <?php print $wid['field_portfolio_website_link']['#items'][0]['value'];?></p>                    <?php endif;?>                    <?php endif;?>                    <?php if(isset($content['sharethis'])):?>                        <?php print render($content['sharethis']);?>                    <?php endif;?>                </div>            </div>            <?php if(isset($multimedia)) :?>            <?php            foreach($multimedia as $key => $value):                $pid = $value['value'];                $data = field_view_value('node', $node, 'field_portfolio_multimedia',$multimedia[$key]);?>                <div class="single-div">                    <?php print render($data['entity']['field_collection_item'][$pid]['field_portfolio_multi_image']);?>                </div>            <?php endforeach;?>            <?php endif;?><?php elseif($style == 'style_2'):?><div id="node-<?php print $node->nid; ?>" class=" <?php print $classes; ?> clearfix"<?php print $attributes; ?>>    <div class="container-single">        <div class="w-container">            <div class="portfolio-tiitle"><?php print $title;?></div>            <div class="subtext-portfolio center"><?php if(isset($content['field_portfolio_subtitle'])): print render($content['field_portfolio_subtitle']); endif;?></div>            <div class="portfolio-line"></div>            <div class="div-slider"><!-- slider begin -->                <div class="w-slider single-slider" data-animation="cross" data-duration="500" data-infinite="1" data-hide-arrows="1" data-easing="ease-in">                    <div class="w-slider-mask">                        <?php                        if(is_array($multimedia)) :                            foreach($multimedia as $key => $value):                                $pid = $value['value'];                                $data = field_view_value('node', $node, 'field_portfolio_multimedia',$multimedia[$key]);                                $wid  = $data['entity']['field_collection_item'][$pid];                                ;?>                                <div class="w-slide">                                    <?php if($wid['field_portfolio_multi_image'][0]['#bundle'] == 'image'):?>                                    <img style="width: 100%;height: 450px" alt="" src="<?php print file_create_url($wid['field_portfolio_multi_image'][0]['file']['#item']['uri']);?>">                                    <?php else:?>                                        <?php print render($wid['field_portfolio_multi_image']);?>                                    <?php endif;?>                                    <?php if(isset($wid['field_portfolio_multi_text'])):?>                                    <a class="slider-link-text" href="<?php if(isset($wid['field_portfolio_multi_link'])): print $wid['field_portfolio_multi_link'][0]['#markup']; endif;?>"><?php print $wid['field_portfolio_multi_text']['#items'][0]['value'];?></a>                                    <?php endif;?>                                </div>                            <?php endforeach;?>                        <?php endif;?>                    </div>                    <div class="w-slider-arrow-left vertical">                        <div class="w-icon-slider-left arrow-slider"></div>                    </div>                    <div class="w-slider-arrow-right vertical">                        <div class="w-icon-slider-right arrow-slider"></div>                    </div>                    <div class="w-slider-nav w-round slide-nav"></div>                </div>            </div>            <div class="w-row row">                <?php if(isset($content['field_portfolio_description'])):?>                <div class="w-col w-col-4">                        <div class="small-tittle"><?php print $content['field_portfolio_description']['#title'];?></div>                        <p class="left"><?php print $content['field_portfolio_description']['#items'][0]['value'];?></p>                </div>                <?php endif;?>                <?php if(isset($content['body'])):?>                <div class="w-col w-col-4 column">                    <p class="left"><?php print $content['body']['#items'][0]['value'];?></p>                </div>                <?php endif;?>                <div class="w-col w-col-4">                    <div class="small-tittle"><?php print t('project details');?></div>                    <?php if(isset($content['field_portfolio_website'][0])):                        $data = $content['field_portfolio_website']['#items'][0]['value'];                        $wid = $content['field_portfolio_website'][0]['entity']['field_collection_item'][$data];                        ?>                        <?php if(isset($wid['field_portfolio_website_title'])):?>                        <p class="left p-margin"><span class="darker"><?php print $wid['field_portfolio_website_title']['#title'];?><?php print t(':');?></span> <?php print $wid['field_portfolio_website_title']['#items'][0]['value'];?></p>                    <?php endif;?>                        <div class="portfolio-line details"></div>                        <p class="left p-margin"><span class="darker"><?php print t('Date:');?></span> <?php print format_date($node->created,'custom','j F, Y');?></p>                        <div class="portfolio-line details"></div>                        <?php if(isset($wid['field_portfolio_website_link'])):?>                            <p class="left p-margin"><span class="darker"><?php print $wid['field_portfolio_website_link']['#title'];?><?php print t(':');?></span> <?php print $wid['field_portfolio_website_link']['#items'][0]['value'];?></p>                        <?php endif;?>                    <?php endif;?>                    <?php if(isset($content['sharethis'])):?>                        <?php print render($content['sharethis']);?>                    <?php endif;?>                </div>            </div><?php elseif ($style == 'style_5'):?><div id="node-<?php print $node->nid; ?>" class=" <?php print $classes; ?> clearfix"<?php print $attributes; ?>>    <section class="section-single-5">        <div class="w-container container-single">            <div class="portfolio-tiitle in-left"><?php print $title;?></div>            <?php if(isset($content['field_portfolio_subtitle'])):?>                <div class="subtext-portfolio"><?php print render($content['field_portfolio_subtitle']);?></div>            <?php endif;?>            <div class="portfolio-line"></div>            <div class="w-row row">                <div class="w-col w-col-4">                    <?php if(isset($content['field_portfolio_description'])):?>                        <div class="small-tittle"><?php print $content['field_portfolio_description']['#title'];?></div>                        <p class="left"><?php print $content['field_portfolio_description']['#items'][0]['value'];?></p>                    <?php endif;?>                    <?php if(isset($content['body'])):?>                        <p class="left"><?php print $content['body']['#items'][0]['value'];?></p>                    <?php endif;?>                    <div class="small-tittle"><?php print t('project details');?></div>                    <?php if(isset($content['field_portfolio_website'][0])):                        $data = $content['field_portfolio_website']['#items'][0]['value'];                        $wid = $content['field_portfolio_website'][0]['entity']['field_collection_item'][$data];                        ?>                        <?php if(isset($wid['field_portfolio_website_title'])):?>                        <p class="left p-margin"><span class="darker"><?php print $wid['field_portfolio_website_title']['#title'];?><?php print t(':');?></span> <?php print $wid['field_portfolio_website_title']['#items'][0]['value'];?></p>                    <?php endif;?>                        <div class="portfolio-line details"></div>                        <p class="left p-margin"><span class="darker"><?php print t('Date:');?></span> <?php print format_date($node->created,'custom','j F, Y');?></p>                        <div class="portfolio-line details"></div>                        <?php if(isset($wid['field_portfolio_website_link'])):?>                        <p class="left p-margin"><span class="darker"><?php print $wid['field_portfolio_website_link']['#title'];?><?php print t(':');?></span> <?php print $wid['field_portfolio_website_link']['#items'][0]['value'];?></p>                    <?php endif;?>                    <?php endif;?>                    <?php if(isset($content['sharethis'])):?>                        <?php print render($content['sharethis']);?>                    <?php endif;?>                </div>                <div class="w-col w-col-8">                    <?php                    foreach($multimedia as $key => $value):                        $pid = $value['value'];                        $data = field_view_value('node', $node, 'field_portfolio_multimedia',$multimedia[$key]);?>                                                                                    <?php print render($data['entity']['field_collection_item'][$pid]['field_portfolio_multi_image']);?>                                                <?php endforeach;?>                </div>            </div>        </div>    </section></div><?php endif;?><?php if($style == 'style_3'):?><div id="node-<?php print $node->nid; ?>" class=" <?php print $classes; ?> clearfix"<?php print $attributes; ?>>    <div class="w-container">        <div class="portfolio-tiitle in-left"><?php print $title;?></div>        <?php if(isset($content['field_portfolio_subtitle'])):?>        <div class="subtext-portfolio"><?php print $content['field_portfolio_subtitle']['#items'][0]['value'];?></div>        <?php endif;?>        <div class="portfolio-line"></div>        <div class="w-row row">            <div class="w-col w-col-8">                <div class="w-slider single-slider" data-animation="over" data-duration="500" data-infinite="1" data-hide-arrows="1"><!-- slider begin -->                    <div class="w-slider-mask">                        <?php                        foreach($multimedia as $key => $value):                        $pid = $value['value'];                        $data = field_view_value('node', $node, 'field_portfolio_multimedia',$multimedia[$key]);                        $current_data = $data['entity']['field_collection_item'][$pid];                        ;?>                        <div class="w-slide">                            <?php if(isset($current_data['field_portfolio_multi_text'])):?>                            <div class="slider-text"><?php print $current_data['field_portfolio_multi_text']['#items'][0]['value'];?></div>                            <?php endif;?>                                            <?php if($current_data['field_portfolio_multi_image'][0]['#bundle'] == 'image'):?>                            <img style="width: 100%; height: 413px" src="<?php print file_create_url($current_data['field_portfolio_multi_image'][0]['file']['#item']['uri']);?>">                            <?php else:?>                                    <?php print render($current_data['field_portfolio_multi_image']);?>                                <?php endif;?>                        </div>                        <?php endforeach;?>                    </div>                    <div class="w-slider-arrow-left vertical">                        <div class="w-icon-slider-left arrow-slider"></div>                    </div>                    <div class="w-slider-arrow-right vertical">                        <div class="w-icon-slider-right arrow-slider"></div>                    </div>                    <div class="w-slider-nav w-round slide-nav"></div>                </div>            </div>            <div class="w-col w-col-4 column-iphone">                <?php if(isset($content['field_portfolio_description'])):?>                <div class="small-tittle"><?php print $content['field_portfolio_description']['#title'];?></div>                <p class="left"><?php print $content['field_portfolio_description']['#items'][0]['value'];?></p>                <?php endif;?>                <div class="small-tittle"><?php print t('project details');?></div>                <?php if(isset($content['field_portfolio_website'][0])):                $data = $content['field_portfolio_website']['#items'][0]['value'];                $wid = $content['field_portfolio_website'][0]['entity']['field_collection_item'][$data];                ?>                <?php if(isset($wid['field_portfolio_website_title'])):?>                <p class="left p-margin"><span class="darker"><?php print $wid['field_portfolio_website_title']['#title'];?><?php print t(':');?></span> <?php print $wid['field_portfolio_website_title']['#items'][0]['value'];?></p>                <?php endif;?>                <div class="portfolio-line details"></div>                <p class="left p-margin"><span class="darker"><?php print t('Date:');?></span> <?php print format_date($node->created,'custom','j F, Y');?></p>                <div class="portfolio-line details"></div>                <?php if(isset($wid['field_portfolio_website_link'])):?>                <p class="left p-margin"><span class="darker"><?php print $wid['field_portfolio_website_link']['#title'];?><?php print t(':');?></span> <?php print $wid['field_portfolio_website_link']['#items'][0]['value'];?></p>                <?php endif;?>                <?php endif;?>                <?php if(isset($content['sharethis'])):?>                    <?php print render($content['sharethis']);?>                <?php endif;?>            </div>        </div>    </div>    <div class="logo-section single">        <div class="w-container">            <?php if(isset($content['clients_entity_view_1'])):?>                <?php print render($content['clients_entity_view_1']);?>            <?php endif;?>        </div></div><?php endif;?><?php if ($style == 'style_4'):?>    <section class="section-single-4">        <div class="w-container">            <div class="portfolio-tiitle in-left single-four"><?php print $title;?></div>            <?php if(isset($content['field_portfolio_subtitle'])):?>            <div class="subtext-portfolio four_single"><?php print $content['field_portfolio_subtitle']['#items'][0]['value'];?></div>            <?php endif;?>        </div>    </section>    <div class="section-single">    <div class="w-container container-single">        <div class="w-row row-gall">            <?php            foreach($multimedia as $key => $value):            $pid = $value['value'];            $data = field_view_value('node', $node, 'field_portfolio_multimedia',$multimedia[$key]);            $current_data = $data['entity']['field_collection_item'][$pid];            ?>            <div class="w-col w-col-4 column-gallery">                <?php if($current_data['field_portfolio_multi_image'][0]['#bundle'] == 'image'):?>                <img src="<?php print file_create_url($current_data['field_portfolio_multi_image'][0]['file']['#item']['uri']);?>">                <?php else:?>                                <?php print render($current_data['field_portfolio_multi_image']);?>                            <?php endif;?>                            <?php if(isset($current_data['field_portfolio_multi_text'])):?>                <a class="w-inline-block galler-overlay" href="<?php if(isset($current_data['field_portfolio_multi_link'])): print $current_data['field_portfolio_multi_link']['#items'][0]['value'];  endif;?>">                    <div class="text-gallery"><?php print $current_data['field_portfolio_multi_text']['#items'][0]['value'];?></div>                    <?php endif;?>                </a>            </div>            <?php endforeach;?>        </div>        <div class="w-row row">            <div class="w-col w-col-4">                <?php if(isset($content['field_portfolio_description'])):?>                <div class="small-tittle"><?php print $content['field_portfolio_description']['#title'];?></div>                <p class="left"><?php print $content['field_portfolio_description']['#items'][0]['value'];?></p>                <?php endif;?>            </div>            <div class="w-col w-col-4 column">                <?php if(isset($content['body'])):?>                <p class="left"><?php print $content['body']['#items'][0]['value'];?></p>                <?php endif;?>            </div>            <div class="w-col w-col-4">                <div class="small-tittle"><?php print t('project details');?></div>                <?php if(isset($content['field_portfolio_website'][0])):                $data = $content['field_portfolio_website']['#items'][0]['value'];                $wid = $content['field_portfolio_website'][0]['entity']['field_collection_item'][$data];                ?>                <?php if(isset($wid['field_portfolio_website_title'])):?>                <p class="left p-margin"><span class="darker"><?php print $wid['field_portfolio_website_title']['#title'];?><?php print t(':');?></span> <?php print $wid['field_portfolio_website_title']['#items'][0]['value'];?></p>                <?php endif;?>                <div class="portfolio-line details"></div>                <p class="left p-margin"><span class="darker"><?php print t('Date:');?></span> <?php print format_date($node->created,'custom','j F, Y');?></p>                <div class="portfolio-line details"></div>                <?php if(isset($wid['field_portfolio_website_link'])):?>                <p class="left p-margin"><span class="darker"><?php print $wid['field_portfolio_website_link']['#title'];?><?php print t(':');?></span> <?php print $wid['field_portfolio_website_link']['#items'][0]['value'];?></p>                <?php endif;?>                <?php endif;?>                <?php if(isset($content['sharethis'])):?>                    <?php print render($content['sharethis']);?>                <?php endif;?>            </div>        </div>    </div>    </div><?php endif;?><?php //print render($content['flippy_pager']);?>
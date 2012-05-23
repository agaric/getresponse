<?php

/**
 * @file
 * Functions for RSS.
 */

define('ELEMENT_CONTENT_ONLY', TRUE);
define('ELEMENT_PRESERVE_TAGS', FALSE);
class GetResponseRSS {
  public $urlFeed;
  public $limit = 10;
  protected $xml;

  /**
   * Functions valueIn.
   */
  protected function valueIn($element_name, $xml, $content_only = TRUE) {
    if ($xml == FALSE) {
      return FALSE;
    }
    $found = preg_match('#<' . $element_name . '(?:\s+[^>]+)?>(.*?)' . '</' . $element_name . '>#s', $xml, $matches);
    if ($found != FALSE) {
      if ($content_only) {
        return $matches[1];
      }
      else {
        return $matches[0];
      }
    }
    return FALSE;
  }

  /**
   * Functions elementSet.
   */
  protected function elementSet($element_name, $xml, $content_only = FALSE) {
    if ($xml == FALSE) {
      return FALSE;
    }
    $found = preg_match_all('#<' . $element_name . '(?:\s+[^>]+)?>' . '(.*?)</' . $element_name . '>#s', $xml, $matches, PREG_PATTERN_ORDER);
    if ($found != FALSE) {
      if ($content_only) {
        return $matches[1];
      }
      else {
        return $matches[0];
      }
    }
    return FALSE;
  }

  /**
   * Functions makeSafe.
   */
  protected function makeSafe($string) {
    $string = preg_replace('#<!\[CDATA\[.*?\]\]>#s', '', $string);
    $string = strip_tags($string);
    $string = str_replace('<', '&lt;', $string);
    $string = str_replace('>', '&gt;', $string);
    $string = str_replace('(', '&#40;', $string);
    $string = str_replace(')', '&#41;', $string);
    $string = str_replace('"', '&quot;', $string);
    $string = str_replace('\'', '&#039;', $string);

    return $string;
  }

  /**
   * Functions curlRss.
   */
  function curlRss() {
    if (function_exists('curl_init')) {
      $ch = curl_init();
      curl_setopt($ch, CURLOPT_URL, $this->urlFeed);
      curl_setopt($ch, CURLOPT_HEADER, FALSE);
      curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
      $this->xml = curl_exec($ch);
      curl_close($ch);
      return TRUE;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Functions renderRss.
   */
  function renderRss() {
    if ($this->curlRss()) {
      $news_items = $this->elementSet('item', $this->xml);

      if (is_array($news_items)) {
        foreach ($news_items as $item) {
          $title = $this->valueIn('title', $item);
          $url = $this->valueIn('link', $item);
          $description = $this->valueIn('description', $item);
          $timestamp = strtotime($this->valueIn('pubDate', $item));
          $item_array[] = array(
            'title' => $title,
            'url' => $url,
            'description' => $description,
            'timestamp' => $timestamp,
          );
        }
        $html = '<ul class="GR_rss_ul">';
        $count = 0;

        if (sizeof($news_items) > 0) {
          foreach ($item_array as $item) {
            $html .= '<li class="GR_rss_li">';
            $html .= '<a href="' . $this->makeSafe($item['url']) . '" target="_blank">' . $this->makeSafe($item['title']) . '</a>';
            $html .= '</li>';
            // Limit the output.
            if (++$count == $this->limit) {
              break;
            }
          }
          $html .= '<ul>';
        }
      }
      else {
        $html = 'No RSS found.';
      }
    }
    else {
      $html = "Can't connect to RSS.";
    }

    return $html;
  }
}

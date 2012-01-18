<?php

/**
 * @file
 * Functions for RSS.
 */

define('ELEMENT_CONTENT_ONLY', true);
define('ELEMENT_PRESERVE_TAGS', false);

Class GetResponseRSS
{
	public $url_feed;
	public $limit = 10;
	private $xml;

	private function value_in($element_name, $xml, $content_only = true) {
		if ($xml == false) {
			return false;
		}
		$found = preg_match('#<'.$element_name.'(?:\s+[^>]+)?>(.*?)'.
				'</'.$element_name.'>#s', $xml, $matches);
		if ($found != false) {
			if ($content_only) {
				return $matches[1];  //ignore the enclosing tags
			} else {
				return $matches[0];  //return the full pattern match
			}
		}
		// No match found: return false.
		return false;
	}

	private function element_set($element_name, $xml, $content_only = false) {
		if ($xml == false) {
			return false;
		}
		$found = preg_match_all('#<'.$element_name.'(?:\s+[^>]+)?>' .
				'(.*?)</'.$element_name.'>#s',
				$xml, $matches, PREG_PATTERN_ORDER);
		if ($found != false) {
			if ($content_only) {
				return $matches[1];  //ignore the enlosing tags
			} else {
				return $matches[0];  //return the full pattern match
			}
		}
		// No match found: return false.
		return false;
	}

	private function make_safe($string)
	{
		$string = preg_replace('#<!\[CDATA\[.*?\]\]>#s', '', $string);
		$string = strip_tags($string);
		// The next line requires PHP 5.2.3, unfortunately.
		//$string = htmlentities($string, ENT_QUOTES, 'UTF-8', false);
		$string = str_replace('<', '&lt;', $string);
		$string = str_replace('>', '&gt;', $string);
		$string = str_replace('(', '&#40;', $string);
		$string = str_replace(')', '&#41;', $string);
		$string = str_replace('"', '&quot;', $string);
		$string = str_replace('\'', '&#039;', $string);
		return $string;
	}

	function curl_rss()
	{
		if ( function_exists( 'curl_init' ) )
		{
			$ch = curl_init();
			curl_setopt($ch, CURLOPT_URL, $this->url_feed);
			curl_setopt($ch, CURLOPT_HEADER, false);
			curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
			$this->xml = curl_exec($ch);
			curl_close($ch);
			return true;
		} else {
			return false;
		}
	}

	function render_rss()
	{
		if ( $this->curl_rss() ) {
			$news_items = $this->element_set('item', $this->xml);

			if ( is_array($news_items) )
			{
				foreach($news_items as $item) {
					$title = $this->value_in('title', $item);
					$url = $this->value_in('link', $item);
					$description = $this->value_in('description', $item);
					$timestamp = strtotime($this->value_in('pubDate', $item));
					$item_array[] = array(
							'title' => $title,
							'url' => $url,
							'description' => $description,
							'timestamp' => $timestamp
					);
				}
				$html = '<ul class="GR_rss_ul">';
				$count = 0;

				if (sizeof($news_items) > 0) {
						
					foreach ($item_array as $item) {
						$html .= '<li class="GR_rss_li">';
						$html .= '<a href="'.$this->make_safe($item['url']).'" target="_blank">'.$this->make_safe($item['title']).'</a>';
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




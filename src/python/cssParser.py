import cssutils
import json

def parse_css(css_string):
    parser = cssutils.CSSParser()
    stylesheet = parser.parseString(css_string)

    css_rules = []
    for rule in stylesheet:
        if rule.type == rule.STYLE_RULE:
            selector = rule.selectorText
            properties = {}
            for property in rule.style:
                properties[property.name] = property.value
            css_rules.append({"selector": selector, "properties": properties})

    return json.dumps(css_rules)
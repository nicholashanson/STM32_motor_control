import re

USER_CODE_REGEX = re.compile(
    r'/\*\s*USER CODE BEGIN\s+([^\s*]+)\s*\*/(.*?)/\*\s*USER CODE END\s+\1\s*\*/',
    re.DOTALL
)

def extract_user_code_sections(filepath):
    with open(filepath, 'r') as f:
        content = f.read()

    sections = {}
    for match in USER_CODE_REGEX.finditer(content):
        section_name = match.group(1).strip()
        section_body = match.group(2).strip()
        sections[section_name] = section_body
    return sections

def insert_user_code_sections(base_content, user_sections):
    def replacer(match):
        section_name = match.group(1).strip()
        existing = match.group(2)
        replacement = user_sections.get(section_name, existing)
        return f'/* USER CODE BEGIN {section_name} */\n{replacement}\n/* USER CODE END {section_name} */'

    return USER_CODE_REGEX.sub(replacer, base_content)

def sync_test_main(main_c_path, test_main_c_path):
    # Extract user code sections from test_main.c
    user_sections = extract_user_code_sections(test_main_c_path)

    # Load main.c 
    with open(main_c_path, 'r') as f:
        main_c_content = f.read()

    # Replace user code blocks with test_main versions
    updated_content = insert_user_code_sections(main_c_content, user_sections)

    # Write to test_main.c
    with open(test_main_c_path, 'w') as f:
        f.write(updated_content)

    print("test_main.c synced with main.c. User code blocks preserved.")

if __name__ == '__main__':
    sync_test_main('Core/Src/main.c', 'Test/test_main.c')

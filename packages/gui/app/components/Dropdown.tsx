import React from 'react';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { solid } from '@fortawesome/fontawesome-svg-core/import.macro';
import { Group } from './Group';
import { Text } from './Text';

type DropdownProps = {
  label?: string;
  options: { value: string; name: string }[];
  value: string;
  tooltip?: string;
  onChange: (value: string) => void;
}
export const Dropdown = ({ label, options, value, tooltip, onChange }: DropdownProps) => {
  return (
    <label>
      <Group direction='vertical'>
        <Group direction='horizontal'>
          <Text size='xl' className="label-main">{label}</Text>
          {tooltip && <a className="tooltip-link" id={tooltip} href="#"><FontAwesomeIcon icon={solid('question-circle')}/></a>}
        </Group>
        <select value={value} onChange={(e) => onChange(e.target.value)}>
          {options.map((option) => (
            <option key={option.value} value={option.value}>
              {option.name}
            </option>
          ))}
        </select>
      </Group>
    </label>
  );
};

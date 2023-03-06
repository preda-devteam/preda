import *  as React from 'react';
import clss from 'classnames';


interface MoreSwitchType {
  onChange: (s: boolean) => void
  value: boolean
}
const MoreSwitch = ({ onChange, value }: MoreSwitchType) => {
  return (
    <div className="switch-box" onClick={() => {
      onChange && onChange(!value);
    }}>
      <span>{ value ? 'Collapse' : 'View More'}</span>
      <div className={clss({'open': value},  'switch-raw')}></div>
    </div>
  );
};

export default MoreSwitch;
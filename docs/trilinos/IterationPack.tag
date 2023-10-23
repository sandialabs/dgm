<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="class">
    <name>IterationPack::Algorithm</name>
    <filename>classIterationPack_1_1Algorithm.html</filename>
    <class kind="class">IterationPack::Algorithm::AlgorithmInterrupted</class>
    <class kind="class">IterationPack::Algorithm::AlreadyExists</class>
    <class kind="class">IterationPack::Algorithm::DoesNotExist</class>
    <class kind="class">IterationPack::Algorithm::InvalidConfigChange</class>
    <class kind="class">IterationPack::Algorithm::InvalidControlProtocal</class>
    <class kind="class">IterationPack::Algorithm::InvalidRunningState</class>
    <member kind="function">
      <type></type>
      <name>STANDARD_MEMBER_COMPOSITION_MEMBERS</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a92887d4637355a474118f42feb7674bb</anchor>
      <arglist>(std::string, interrupt_file_name)</arglist>
    </member>
    <member kind="enumeration">
      <name>ERunningState</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a56618b74e544854bbbdc3663aed317c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; AlgorithmState &gt;</type>
      <name>state_ptr_t</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>ada352fda0a3d450b5b28acd4116d9c8e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; AlgorithmTracker &gt;</type>
      <name>track_ptr_t</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a74d5c2f1afab5fa08ad7c37b73d272ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; AlgorithmStep &gt;</type>
      <name>step_ptr_t</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a47a2fda88a3a8569bda6425969ca95ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>size_t</type>
      <name>poss_type</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a8cf88246e81956768d6693cbe86f1523</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Algorithm</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a8f6d9cac7e0c8873436a20f5c5c2adc7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Algorithm</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>ae4ae75fcae1eaf91a45b436672178715</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_state</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a3ad2f76c589bfeec11916ae3944df82c</anchor>
      <arglist>(const state_ptr_t &amp;state)</arglist>
    </member>
    <member kind="function">
      <type>state_ptr_t &amp;</type>
      <name>get_state</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>abd7ba05ff452fabdf09ddd6ba78fb8ba</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const state_ptr_t &amp;</type>
      <name>get_state</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>af6d27892dd1e0a90aa26ba507b0f5790</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>AlgorithmState &amp;</type>
      <name>state</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a12993867ae1806ddc0d6135452dc3cf1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const AlgorithmState &amp;</type>
      <name>state</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a37ef2b147d1ab059767b2a38c11efd42</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_track</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>afa3f427d23dececef23993ff0ec353b6</anchor>
      <arglist>(const track_ptr_t &amp;track)</arglist>
    </member>
    <member kind="function">
      <type>track_ptr_t &amp;</type>
      <name>get_track</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>abeac11e8d8a63b58a1b2c80c582137ac</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const track_ptr_t &amp;</type>
      <name>get_track</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>abf93df6bae32e5b511066926f1302097</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>AlgorithmTracker &amp;</type>
      <name>track</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a5501fc239a0b417d6eec0cc1e90520a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const AlgorithmTracker &amp;</type>
      <name>track</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a818d95e5c7f2bcc298eb82a5e84462df</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>max_iter</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>af8b0bd86d8ca6ef3dc7ed2cb30a315b2</anchor>
      <arglist>(size_t max_iter)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>max_iter</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a0da8c84296fd37419ff7de34b449cb82</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>max_run_time</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a1bbffddbbc63bb4547170bf214c24652</anchor>
      <arglist>(double max_iter)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>max_run_time</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a5fb7c36e95ea468d0cb43091c733c240</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>num_steps</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a0ad2686688a0fb4aad87244e9c599480</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual poss_type</type>
      <name>get_step_poss</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a5f8e5fea7691c33104de16a176c593df</anchor>
      <arglist>(const std::string &amp;step_name) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const std::string &amp;</type>
      <name>get_step_name</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a90b5e0ad5ab931eec026ab6263ce6dc9</anchor>
      <arglist>(poss_type step_poss) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual step_ptr_t &amp;</type>
      <name>get_step</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a88fc28b60855fbda9a2bc26eb3168e3d</anchor>
      <arglist>(poss_type step_poss)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const step_ptr_t &amp;</type>
      <name>get_step</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a55aa0b2f18e5d40fea458590ea0833f5</anchor>
      <arglist>(poss_type step_poss) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>num_assoc_steps</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>ac23e66e14203de9ce46ea839e7a81c72</anchor>
      <arglist>(poss_type step_poss, EAssocStepType type) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual poss_type</type>
      <name>get_assoc_step_poss</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>aae7228a4662df5e682c3cf8034c47578</anchor>
      <arglist>(poss_type step_poss, EAssocStepType type, const std::string &amp;assoc_step_name) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const std::string &amp;</type>
      <name>get_assoc_step_name</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a40df3e58d4d1e8560b1f8eb7ebc020bf</anchor>
      <arglist>(poss_type step_poss, EAssocStepType type, poss_type assoc_step_poss) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual step_ptr_t &amp;</type>
      <name>get_assoc_step</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a8dd06ec6f9e9ed3b5a4f2a1589d3d91b</anchor>
      <arglist>(poss_type step_poss, EAssocStepType type, poss_type assoc_step_poss)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const step_ptr_t &amp;</type>
      <name>get_assoc_step</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a83a5f0ef77ce6f490224ecc79700f243</anchor>
      <arglist>(poss_type step_poss, EAssocStepType type, poss_type assoc_step_poss) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>insert_step</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a23818d46fbf4c08dd1d72f910619ab1c</anchor>
      <arglist>(poss_type step_poss, const std::string &amp;step_name, const step_ptr_t &amp;step)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>change_step_name</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>ab475b17c7c0da53f4212891dbf2fd5d1</anchor>
      <arglist>(poss_type step_poss, const std::string &amp;new_name)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>replace_step</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>af8ac5331811c587c0255037389efeebe</anchor>
      <arglist>(poss_type step_poss, const step_ptr_t &amp;step)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>remove_step</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a023ba0894db298c3a5e0d52f132708cc</anchor>
      <arglist>(poss_type step_poss)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>insert_assoc_step</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a007fa6dedd15d99bc3a4cfc4bd1748b4</anchor>
      <arglist>(poss_type step_poss, EAssocStepType type, poss_type assoc_step_poss, const std::string &amp;assoc_step_name, const step_ptr_t &amp;assoc_step)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>remove_assoc_step</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>aa614cf0c42b55d61be44b11130c71190</anchor>
      <arglist>(poss_type step_poss, EAssocStepType type, poss_type assoc_step_poss)</arglist>
    </member>
    <member kind="function">
      <type>ERunningState</type>
      <name>running_state</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a1c8dfd39d219d160a78071e5041412f8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>begin_config_update</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>adb4309d3afb1871aaede0a07258fac59</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>end_config_update</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a89093518cf1f72295a4cb8aba6fc5103</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>do_step_next</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>abf5011a0d67fd3c5dd90478fe558e0ec</anchor>
      <arglist>(const std::string &amp;step_name)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>do_step_next</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>ab5e42017c1d6da060dcd263cb4980c5f</anchor>
      <arglist>(poss_type step_poss)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const std::string &amp;</type>
      <name>what_is_next_step_name</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>ab98901c4fe76be1ba22a3cea10c06f4a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual poss_type</type>
      <name>what_is_next_step_poss</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a0496b5b20d028ac51dd47dc6af38032d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>do_step</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a126cb9b7bdc5a559ceeebb5c7e175971</anchor>
      <arglist>(const std::string &amp;step_name)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>do_step</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a75052ad1c71ff3092caee3a472597fe1</anchor>
      <arglist>(poss_type step_poss)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>terminate</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>ad44fef207787b50855860b1fa6a3b483</anchor>
      <arglist>(bool success)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual EAlgoReturn</type>
      <name>do_algorithm</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a725e34f1509fd0db3a93359c96f8426c</anchor>
      <arglist>(poss_type step_poss=1)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>print_steps</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>ae11324ed7bebe9521b0ad762dfddda4d</anchor>
      <arglist>(std::ostream &amp;out) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>print_algorithm</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>aecb689e23ff239817fb25601aa45cd0b</anchor>
      <arglist>(std::ostream &amp;out) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_algo_timing</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>aeceb7d75de08bb0cf71b503d35495db0</anchor>
      <arglist>(bool algo_timing)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>algo_timing</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>ac92b40917490d751aa5fca51ef4e1082</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>print_algorithm_times</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a87dcfa8219c9292b8247fa59ab27d937</anchor>
      <arglist>(std::ostream &amp;out) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_step_times_k</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>a090d3bff5fa8d24138e7ff9b86cfb2c4</anchor>
      <arglist>(int offset, double step_times[]) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_final_step_stats</name>
      <anchorfile>classIterationPack_1_1Algorithm.html</anchorfile>
      <anchor>aff150e63051f8ec3abf03542a1c15e05</anchor>
      <arglist>(size_t step, double *total, double *average, double *min, double *max, double *percent) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>IterationPack::Algorithm::AlgorithmInterrupted</name>
    <filename>classIterationPack_1_1Algorithm_1_1AlgorithmInterrupted.html</filename>
  </compound>
  <compound kind="class">
    <name>IterationPack::Algorithm::AlreadyExists</name>
    <filename>classIterationPack_1_1Algorithm_1_1AlreadyExists.html</filename>
  </compound>
  <compound kind="class">
    <name>IterationPack::Algorithm::DoesNotExist</name>
    <filename>classIterationPack_1_1Algorithm_1_1DoesNotExist.html</filename>
  </compound>
  <compound kind="class">
    <name>IterationPack::Algorithm::InvalidConfigChange</name>
    <filename>classIterationPack_1_1Algorithm_1_1InvalidConfigChange.html</filename>
  </compound>
  <compound kind="class">
    <name>IterationPack::Algorithm::InvalidControlProtocal</name>
    <filename>classIterationPack_1_1Algorithm_1_1InvalidControlProtocal.html</filename>
  </compound>
  <compound kind="class">
    <name>IterationPack::Algorithm::InvalidRunningState</name>
    <filename>classIterationPack_1_1Algorithm_1_1InvalidRunningState.html</filename>
  </compound>
  <compound kind="class">
    <name>IterationPack::AlgorithmSetOptions</name>
    <filename>classIterationPack_1_1AlgorithmSetOptions.html</filename>
    <base>OptionsFromStreamPack::SetOptionsFromStreamNode</base>
    <base>OptionsFromStreamPack::SetOptionsToTargetBase</base>
    <member kind="function">
      <type></type>
      <name>AlgorithmSetOptions</name>
      <anchorfile>classIterationPack_1_1AlgorithmSetOptions.html</anchorfile>
      <anchor>a8224c0b9dec4e87d815da23802ddb640</anchor>
      <arglist>(Algorithm *target=0, const char opt_grp_name[]=&quot;IterationPack_Algorithm&quot;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setOption</name>
      <anchorfile>classIterationPack_1_1AlgorithmSetOptions.html</anchorfile>
      <anchor>a1d000c2928a4e0be1c3485edee77185d</anchor>
      <arglist>(int option_num, const std::string &amp;option_value)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>IterationPack::AlgorithmState</name>
    <filename>classIterationPack_1_1AlgorithmState.html</filename>
    <class kind="class">IterationPack::AlgorithmState::AlreadyExists</class>
    <class kind="class">IterationPack::AlgorithmState::DoesNotExist</class>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~AlgorithmState</name>
      <anchorfile>classIterationPack_1_1AlgorithmState.html</anchorfile>
      <anchor>a99ede27990341fa09f4a044e4a0d72c9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="typedef">
      <type>size_t</type>
      <name>iq_id_type</name>
      <anchorfile>classIterationPack_1_1AlgorithmState.html</anchorfile>
      <anchor>a75585f507200ef4728a059e9fd36e9ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; IterQuantity &gt;</type>
      <name>IQ_ptr</name>
      <anchorfile>classIterationPack_1_1AlgorithmState.html</anchorfile>
      <anchor>ab8acc1d65e645473dfd988066967b82b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AlgorithmState</name>
      <anchorfile>classIterationPack_1_1AlgorithmState.html</anchorfile>
      <anchor>a312a0c33a0918d8752003476d3049162</anchor>
      <arglist>(size_t reserve_size=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>k</name>
      <anchorfile>classIterationPack_1_1AlgorithmState.html</anchorfile>
      <anchor>ac66ab332bd340a516d08c4743163bb2f</anchor>
      <arglist>(int k)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>k</name>
      <anchorfile>classIterationPack_1_1AlgorithmState.html</anchorfile>
      <anchor>a29045f1df02bcacd3d397739f238ccf0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>incr_k</name>
      <anchorfile>classIterationPack_1_1AlgorithmState.html</anchorfile>
      <anchor>aa4c192ddb9739d4783cd4dfdd20433c8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>num_iter_quant</name>
      <anchorfile>classIterationPack_1_1AlgorithmState.html</anchorfile>
      <anchor>a46f07bfb6d877789134bee3a6ad59e49</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual iq_id_type</type>
      <name>set_iter_quant</name>
      <anchorfile>classIterationPack_1_1AlgorithmState.html</anchorfile>
      <anchor>a44704cb3a1ad1290538f575eedd5a2cd</anchor>
      <arglist>(const std::string &amp;iq_name, const IQ_ptr &amp;iq)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>erase_iter_quant</name>
      <anchorfile>classIterationPack_1_1AlgorithmState.html</anchorfile>
      <anchor>a961f8e0bf9bf3afd6f6a4c1e64bff55d</anchor>
      <arglist>(const std::string &amp;iq_name)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual iq_id_type</type>
      <name>get_iter_quant_id</name>
      <anchorfile>classIterationPack_1_1AlgorithmState.html</anchorfile>
      <anchor>af18185b71075ec8a21a3562f9b8e1cc6</anchor>
      <arglist>(const std::string &amp;iq_name) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual IQ_ptr &amp;</type>
      <name>get_iter_quant</name>
      <anchorfile>classIterationPack_1_1AlgorithmState.html</anchorfile>
      <anchor>a60f83b9dc07f0ce3c9ac08a18b956485</anchor>
      <arglist>(iq_id_type iq_id)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const IQ_ptr &amp;</type>
      <name>get_iter_quant</name>
      <anchorfile>classIterationPack_1_1AlgorithmState.html</anchorfile>
      <anchor>add52c33173fb70cb08b14b6ea55516a2</anchor>
      <arglist>(iq_id_type iq_id) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual IterQuantity &amp;</type>
      <name>iter_quant</name>
      <anchorfile>classIterationPack_1_1AlgorithmState.html</anchorfile>
      <anchor>a4419573ff59aab50341840cd6a8ba4f0</anchor>
      <arglist>(const std::string &amp;iq_name)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const IterQuantity &amp;</type>
      <name>iter_quant</name>
      <anchorfile>classIterationPack_1_1AlgorithmState.html</anchorfile>
      <anchor>acbe2331472a91eedfe9387d1ba5fdd59</anchor>
      <arglist>(const std::string &amp;iq_name) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual IterQuantity &amp;</type>
      <name>iter_quant</name>
      <anchorfile>classIterationPack_1_1AlgorithmState.html</anchorfile>
      <anchor>a90f8939fb329c81a88af7d6ba4742919</anchor>
      <arglist>(iq_id_type iq_id)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const IterQuantity &amp;</type>
      <name>iter_quant</name>
      <anchorfile>classIterationPack_1_1AlgorithmState.html</anchorfile>
      <anchor>aaeb643ece2ced3385992248561be6bff</anchor>
      <arglist>(iq_id_type iq_id) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>next_iteration</name>
      <anchorfile>classIterationPack_1_1AlgorithmState.html</anchorfile>
      <anchor>a05d517cb2fcd4e0543f33e26f9e6a311</anchor>
      <arglist>(bool incr_k=true)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>dump_iter_quant</name>
      <anchorfile>classIterationPack_1_1AlgorithmState.html</anchorfile>
      <anchor>a385c6c4473902ec072674611a2eb7a16</anchor>
      <arglist>(std::ostream &amp;out) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>IterationPack::AlgorithmState::AlreadyExists</name>
    <filename>classIterationPack_1_1AlgorithmState_1_1AlreadyExists.html</filename>
  </compound>
  <compound kind="class">
    <name>IterationPack::AlgorithmState::DoesNotExist</name>
    <filename>classIterationPack_1_1AlgorithmState_1_1DoesNotExist.html</filename>
  </compound>
  <compound kind="class">
    <name>IterationPack::AlgorithmStep</name>
    <filename>classIterationPack_1_1AlgorithmStep.html</filename>
    <member kind="typedef">
      <type>size_t</type>
      <name>poss_type</name>
      <anchorfile>classIterationPack_1_1AlgorithmStep.html</anchorfile>
      <anchor>a93fbd7b6e2a0f8f9f64dab1afb179ba1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>do_step</name>
      <anchorfile>classIterationPack_1_1AlgorithmStep.html</anchorfile>
      <anchor>a4f9e70c6f9e6017d49cebecef2c687d4</anchor>
      <arglist>(Algorithm &amp;algo, poss_type step_poss, EDoStepType type, poss_type assoc_step_poss)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~AlgorithmStep</name>
      <anchorfile>classIterationPack_1_1AlgorithmStep.html</anchorfile>
      <anchor>a2d33ba283c358450fbe0a5492ad2110a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initialize_step</name>
      <anchorfile>classIterationPack_1_1AlgorithmStep.html</anchorfile>
      <anchor>a25befe1506641144d61af41f6d713a13</anchor>
      <arglist>(Algorithm &amp;algo, poss_type step_poss, EDoStepType type, poss_type assoc_step_poss)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>inform_updated</name>
      <anchorfile>classIterationPack_1_1AlgorithmStep.html</anchorfile>
      <anchor>ac4db90751c67d2f7571c696555c8ba12</anchor>
      <arglist>(Algorithm &amp;algo, poss_type step_poss, EDoStepType type, poss_type assoc_step_poss)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>finalize_step</name>
      <anchorfile>classIterationPack_1_1AlgorithmStep.html</anchorfile>
      <anchor>aa842e050263a4dd6f78aecdd4a93622a</anchor>
      <arglist>(Algorithm &amp;algo, poss_type step_poss, EDoStepType type, poss_type assoc_step_poss)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>print_step</name>
      <anchorfile>classIterationPack_1_1AlgorithmStep.html</anchorfile>
      <anchor>ac7d5e186e7ad015f40791a40f892383d</anchor>
      <arglist>(const Algorithm &amp;algo, poss_type step_poss, EDoStepType type, poss_type assoc_step_poss, std::ostream &amp;out, const std::string &amp;leading_str) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>IterationPack::AlgorithmTracker</name>
    <filename>classIterationPack_1_1AlgorithmTracker.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~AlgorithmTracker</name>
      <anchorfile>classIterationPack_1_1AlgorithmTracker.html</anchorfile>
      <anchor>af5dbd975997f2e65678cb76c55941414</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; std::ostream &gt;</type>
      <name>ostream_ptr_t</name>
      <anchorfile>classIterationPack_1_1AlgorithmTracker.html</anchorfile>
      <anchor>ace5f67b29dc03531e2bc8572ef935467</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AlgorithmTracker</name>
      <anchorfile>classIterationPack_1_1AlgorithmTracker.html</anchorfile>
      <anchor>a46decab3c727cc7cde716db2fe475d7a</anchor>
      <arglist>(const ostream_ptr_t &amp;journal_out)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>initialize</name>
      <anchorfile>classIterationPack_1_1AlgorithmTracker.html</anchorfile>
      <anchor>abe14ab771a21ef84aebff56a3cbb73a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>output_iteration</name>
      <anchorfile>classIterationPack_1_1AlgorithmTracker.html</anchorfile>
      <anchor>ad74038bc2b06b7b0972b51786a4f9704</anchor>
      <arglist>(const Algorithm &amp;algo) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>output_final</name>
      <anchorfile>classIterationPack_1_1AlgorithmTracker.html</anchorfile>
      <anchor>adb476a91cc6e1c0c7493fab84779f32e</anchor>
      <arglist>(const Algorithm &amp;algo, EAlgoReturn algo_return) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_journal_out</name>
      <anchorfile>classIterationPack_1_1AlgorithmTracker.html</anchorfile>
      <anchor>ae45112ebcc25de52d15b98819ced117c</anchor>
      <arglist>(const ostream_ptr_t &amp;journal_out)</arglist>
    </member>
    <member kind="function">
      <type>const ostream_ptr_t &amp;</type>
      <name>get_journal_out</name>
      <anchorfile>classIterationPack_1_1AlgorithmTracker.html</anchorfile>
      <anchor>a52eb165458ab2b2448b87806e485035f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::ostream &amp;</type>
      <name>journal_out</name>
      <anchorfile>classIterationPack_1_1AlgorithmTracker.html</anchorfile>
      <anchor>a42897043b918f1ebdd0b1df546e9772b</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>IterationPack::AlgorithmTrackerComposite</name>
    <filename>classIterationPack_1_1AlgorithmTrackerComposite.html</filename>
    <base>IterationPack::AlgorithmTracker</base>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; AlgorithmTracker &gt;</type>
      <name>track_ptr_t</name>
      <anchorfile>classIterationPack_1_1AlgorithmTrackerComposite.html</anchorfile>
      <anchor>ad81480515e9c9ce0098843aba6204159</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::list&lt; track_ptr_t &gt;</type>
      <name>track_list_t</name>
      <anchorfile>classIterationPack_1_1AlgorithmTrackerComposite.html</anchorfile>
      <anchor>a42c6d8be5d5d565ee94800f690cc36ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; std::ostream &gt;</type>
      <name>ostream_ptr_t</name>
      <anchorfile>classIterationPack_1_1AlgorithmTracker.html</anchorfile>
      <anchor>ace5f67b29dc03531e2bc8572ef935467</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AlgorithmTrackerComposite</name>
      <anchorfile>classIterationPack_1_1AlgorithmTrackerComposite.html</anchorfile>
      <anchor>a535bd915794468cd344e74197e145a04</anchor>
      <arglist>(const ostream_ptr_t &amp;journal_out)</arglist>
    </member>
    <member kind="function">
      <type>track_list_t &amp;</type>
      <name>tracks</name>
      <anchorfile>classIterationPack_1_1AlgorithmTrackerComposite.html</anchorfile>
      <anchor>a9c2df6d04e12fb2dbae506a060fc08d6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const track_list_t &amp;</type>
      <name>tracks</name>
      <anchorfile>classIterationPack_1_1AlgorithmTrackerComposite.html</anchorfile>
      <anchor>a6f5b87801b822202fc0f045d06ab629f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~AlgorithmTracker</name>
      <anchorfile>classIterationPack_1_1AlgorithmTracker.html</anchorfile>
      <anchor>af5dbd975997f2e65678cb76c55941414</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AlgorithmTracker</name>
      <anchorfile>classIterationPack_1_1AlgorithmTracker.html</anchorfile>
      <anchor>a46decab3c727cc7cde716db2fe475d7a</anchor>
      <arglist>(const ostream_ptr_t &amp;journal_out)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_journal_out</name>
      <anchorfile>classIterationPack_1_1AlgorithmTracker.html</anchorfile>
      <anchor>ae45112ebcc25de52d15b98819ced117c</anchor>
      <arglist>(const ostream_ptr_t &amp;journal_out)</arglist>
    </member>
    <member kind="function">
      <type>const ostream_ptr_t &amp;</type>
      <name>get_journal_out</name>
      <anchorfile>classIterationPack_1_1AlgorithmTracker.html</anchorfile>
      <anchor>a52eb165458ab2b2448b87806e485035f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::ostream &amp;</type>
      <name>journal_out</name>
      <anchorfile>classIterationPack_1_1AlgorithmTracker.html</anchorfile>
      <anchor>a42897043b918f1ebdd0b1df546e9772b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classIterationPack_1_1AlgorithmTrackerComposite.html</anchorfile>
      <anchor>aa6df69dc4892eb4091f27a6f56672102</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>output_iteration</name>
      <anchorfile>classIterationPack_1_1AlgorithmTrackerComposite.html</anchorfile>
      <anchor>a899a0b68bdac72e37b2cce47fd768368</anchor>
      <arglist>(const Algorithm &amp;algo) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>output_final</name>
      <anchorfile>classIterationPack_1_1AlgorithmTrackerComposite.html</anchorfile>
      <anchor>af77587f885c1ded4defaadd740f54e74</anchor>
      <arglist>(const Algorithm &amp;algo, EAlgoReturn algo_return) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>IterationPack::CastIQMemberBase</name>
    <filename>classIterationPack_1_1CastIQMemberBase.html</filename>
    <member kind="function">
      <type>const std::string &amp;</type>
      <name>iq_name</name>
      <anchorfile>classIterationPack_1_1CastIQMemberBase.html</anchorfile>
      <anchor>a338486309b2252986b48824329df0be9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>exists_in</name>
      <anchorfile>classIterationPack_1_1CastIQMemberBase.html</anchorfile>
      <anchor>a8f75de8773f06ef95c52a389a9c6aac2</anchor>
      <arglist>(const AlgorithmState &amp;s) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>CastIQMemberBase</name>
      <anchorfile>classIterationPack_1_1CastIQMemberBase.html</anchorfile>
      <anchor>a396f80478fd668fe2cfa4473a7a544fd</anchor>
      <arglist>(const std::string iq_name)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>cache_iq_id</name>
      <anchorfile>classIterationPack_1_1CastIQMemberBase.html</anchorfile>
      <anchor>a105b54e0cde88d398c862b11b15a8018</anchor>
      <arglist>(const AlgorithmState &amp;s) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>throw_cast_error</name>
      <anchorfile>classIterationPack_1_1CastIQMemberBase.html</anchorfile>
      <anchor>a50c2b4cfb9531d80c0c265cad4757ce1</anchor>
      <arglist>(const AlgorithmState::iq_id_type iq_id, const std::string &amp;iqa_name) const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const std::string</type>
      <name>iq_name_</name>
      <anchorfile>classIterationPack_1_1CastIQMemberBase.html</anchorfile>
      <anchor>a3a4a065b905f52763a419f69a29e2168</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>AlgorithmState::iq_id_type</type>
      <name>iq_id_</name>
      <anchorfile>classIterationPack_1_1CastIQMemberBase.html</anchorfile>
      <anchor>a9f6ebb8153e78da53e0c28cc54fe4ee7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>IterationPack::CastIQMember</name>
    <filename>classIterationPack_1_1CastIQMember.html</filename>
    <templarg></templarg>
    <base>IterationPack::CastIQMemberBase</base>
    <member kind="function">
      <type></type>
      <name>CastIQMember</name>
      <anchorfile>classIterationPack_1_1CastIQMember.html</anchorfile>
      <anchor>ab2c6b20ad24fb7c782be70b4d1ceacfc</anchor>
      <arglist>(const std::string iq_name)</arglist>
    </member>
    <member kind="function">
      <type>IterQuantityAccess&lt; T &gt; &amp;</type>
      <name>operator()</name>
      <anchorfile>classIterationPack_1_1CastIQMember.html</anchorfile>
      <anchor>abc93db9806ae838446cd473e03d65a6d</anchor>
      <arglist>(AlgorithmState &amp;s) const </arglist>
    </member>
    <member kind="function">
      <type>const IterQuantityAccess&lt; T &gt; &amp;</type>
      <name>operator()</name>
      <anchorfile>classIterationPack_1_1CastIQMember.html</anchorfile>
      <anchor>a8fd9ac42a386222d9f0499782d075f67</anchor>
      <arglist>(const AlgorithmState &amp;s) const </arglist>
    </member>
    <member kind="function">
      <type>const std::string &amp;</type>
      <name>iq_name</name>
      <anchorfile>classIterationPack_1_1CastIQMemberBase.html</anchorfile>
      <anchor>a338486309b2252986b48824329df0be9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>exists_in</name>
      <anchorfile>classIterationPack_1_1CastIQMemberBase.html</anchorfile>
      <anchor>a8f75de8773f06ef95c52a389a9c6aac2</anchor>
      <arglist>(const AlgorithmState &amp;s) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>CastIQMemberBase</name>
      <anchorfile>classIterationPack_1_1CastIQMemberBase.html</anchorfile>
      <anchor>a396f80478fd668fe2cfa4473a7a544fd</anchor>
      <arglist>(const std::string iq_name)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>cache_iq_id</name>
      <anchorfile>classIterationPack_1_1CastIQMemberBase.html</anchorfile>
      <anchor>a105b54e0cde88d398c862b11b15a8018</anchor>
      <arglist>(const AlgorithmState &amp;s) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>throw_cast_error</name>
      <anchorfile>classIterationPack_1_1CastIQMemberBase.html</anchorfile>
      <anchor>a50c2b4cfb9531d80c0c265cad4757ce1</anchor>
      <arglist>(const AlgorithmState::iq_id_type iq_id, const std::string &amp;iqa_name) const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const std::string</type>
      <name>iq_name_</name>
      <anchorfile>classIterationPack_1_1CastIQMemberBase.html</anchorfile>
      <anchor>a3a4a065b905f52763a419f69a29e2168</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>AlgorithmState::iq_id_type</type>
      <name>iq_id_</name>
      <anchorfile>classIterationPack_1_1CastIQMemberBase.html</anchorfile>
      <anchor>a9f6ebb8153e78da53e0c28cc54fe4ee7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>IterationPack::IterQuantity</name>
    <filename>classIterationPack_1_1IterQuantity.html</filename>
    <class kind="class">IterationPack::IterQuantity::NoStorageAvailable</class>
    <class kind="class">IterationPack::IterQuantity::QuanityNotSet</class>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~IterQuantity</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>a87a76d3556a8cbc5c03c4a12bef15d0a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual IterQuantity *</type>
      <name>clone</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>ac09ca7f905c497e3e24010ccd05e59c8</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const char *</type>
      <name>name</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>a31ec9e47261e94e5de1ccfe085c760ab</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>has_storage_k</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>a16993cc4d99866946acd712563525527</anchor>
      <arglist>(int offset) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>updated_k</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>a578dc9c257317ba606796609e004bc04</anchor>
      <arglist>(int offset) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>last_updated</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>a0dcd2d0f5a106abf9e2313bbd6e30d0a</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>will_loose_mem</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>a30f1a063e1b15c83447996b1da0ccfbc</anchor>
      <arglist>(int offset, int set_offset) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>set_not_updated_k</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>a62c88808b6a75ab185e15cda4bd8b43a</anchor>
      <arglist>(int offset)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>set_all_not_updated</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>a88d50103e7b7c1d23d8dc710cf0e5845</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>next_iteration</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>a3807f0c0d1c85d92bbbccfdfc6088926</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>print_concrete_type</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>aa4109c2442b1c2f2ac1afc01abc00f02</anchor>
      <arglist>(std::ostream &amp;out) const =0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assert_has_storage_k</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>a833fdbd2c8174ccc1fea37618593b1f8</anchor>
      <arglist>(int offset) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assert_updated_k</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>ab3208fb4059c83847caa683c13a91735</anchor>
      <arglist>(int offset) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>IterationPack::IterQuantity::NoStorageAvailable</name>
    <filename>classIterationPack_1_1IterQuantity_1_1NoStorageAvailable.html</filename>
  </compound>
  <compound kind="class">
    <name>IterationPack::IterQuantity::QuanityNotSet</name>
    <filename>classIterationPack_1_1IterQuantity_1_1QuanityNotSet.html</filename>
  </compound>
  <compound kind="class">
    <name>IterationPack::IterQuantityAccess</name>
    <filename>classIterationPack_1_1IterQuantityAccess.html</filename>
    <templarg>T_info</templarg>
    <base>IterationPack::IterQuantity</base>
    <member kind="typedef">
      <type>IterQuantity::NoStorageAvailable</type>
      <name>NoStorageAvailable</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccess.html</anchorfile>
      <anchor>ac5f3b6644da9b30f3317324beaddea6a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IterQuantity::QuanityNotSet</type>
      <name>QuanityNotSet</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccess.html</anchorfile>
      <anchor>a97f75516f1990dc08a7830e565053409</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual T_info &amp;</type>
      <name>get_k</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccess.html</anchorfile>
      <anchor>ab4a4e239f61665fac0eaefed2d047cb0</anchor>
      <arglist>(int offset)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const T_info &amp;</type>
      <name>get_k</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccess.html</anchorfile>
      <anchor>a25402de23c73e356741e86f09a93cd4d</anchor>
      <arglist>(int offset) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual T_info &amp;</type>
      <name>set_k</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccess.html</anchorfile>
      <anchor>a58165d811dcadddaa4cb27fd1aea0586</anchor>
      <arglist>(int offset)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual T_info &amp;</type>
      <name>set_k</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccess.html</anchorfile>
      <anchor>a6c7cc870c28423a1d3fc373c11fef353</anchor>
      <arglist>(int set_offset, int get_offset)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~IterQuantity</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>a87a76d3556a8cbc5c03c4a12bef15d0a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual IterQuantity *</type>
      <name>clone</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>ac09ca7f905c497e3e24010ccd05e59c8</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const char *</type>
      <name>name</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>a31ec9e47261e94e5de1ccfe085c760ab</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>has_storage_k</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>a16993cc4d99866946acd712563525527</anchor>
      <arglist>(int offset) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>updated_k</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>a578dc9c257317ba606796609e004bc04</anchor>
      <arglist>(int offset) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>last_updated</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>a0dcd2d0f5a106abf9e2313bbd6e30d0a</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>will_loose_mem</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>a30f1a063e1b15c83447996b1da0ccfbc</anchor>
      <arglist>(int offset, int set_offset) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>set_not_updated_k</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>a62c88808b6a75ab185e15cda4bd8b43a</anchor>
      <arglist>(int offset)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>set_all_not_updated</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>a88d50103e7b7c1d23d8dc710cf0e5845</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>next_iteration</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>a3807f0c0d1c85d92bbbccfdfc6088926</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>print_concrete_type</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>aa4109c2442b1c2f2ac1afc01abc00f02</anchor>
      <arglist>(std::ostream &amp;out) const =0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assert_has_storage_k</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>a833fdbd2c8174ccc1fea37618593b1f8</anchor>
      <arglist>(int offset) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assert_updated_k</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>ab3208fb4059c83847caa683c13a91735</anchor>
      <arglist>(int offset) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>IterationPack::IterQuantityAccessContiguous</name>
    <filename>classIterationPack_1_1IterQuantityAccessContiguous.html</filename>
    <templarg></templarg>
    <base>IterationPack::IterQuantityAccess</base>
    <member kind="typedef">
      <type>IterQuantityAccess&lt; T_info &gt;</type>
      <name>base_t</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccessContiguous.html</anchorfile>
      <anchor>aba32dc427cec0c3c361802989ee49195</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::RCP&lt; const Teuchos::AbstractFactory&lt; T_info &gt; &gt;</type>
      <name>abstract_factory_ptr_t</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccessContiguous.html</anchorfile>
      <anchor>a5b7d6a15c71cbf64f2bc422f1041a41b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Teuchos::AbstractFactoryStd&lt; T_info, T_info &gt;</type>
      <name>abstract_factory_std_t</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccessContiguous.html</anchorfile>
      <anchor>aedacc9a372678bdc48d75e0533b7ea6d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IterQuantity::NoStorageAvailable</type>
      <name>NoStorageAvailable</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccess.html</anchorfile>
      <anchor>ac5f3b6644da9b30f3317324beaddea6a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IterQuantity::QuanityNotSet</type>
      <name>QuanityNotSet</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccess.html</anchorfile>
      <anchor>a97f75516f1990dc08a7830e565053409</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IterQuantityAccessContiguous</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccessContiguous.html</anchorfile>
      <anchor>ae80accb0456b1eefbdd27dd2a59012bf</anchor>
      <arglist>(int num_quantities, const std::string &amp;name, const abstract_factory_ptr_t &amp;abstract_factory=Teuchos::rcp(new abstract_factory_std_t()))</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_factory</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccessContiguous.html</anchorfile>
      <anchor>a197b0735990fc128a6db464fa54149bc</anchor>
      <arglist>(const abstract_factory_ptr_t &amp;abstract_factory)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccessContiguous.html</anchorfile>
      <anchor>aef46c43be207ad43c01771ec7ed9d2df</anchor>
      <arglist>(int num_quantities)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~IterQuantityAccessContiguous</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccessContiguous.html</anchorfile>
      <anchor>a1a3e7e34351ce29ca02f5d2836ca42dd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>num_quantities</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccessContiguous.html</anchorfile>
      <anchor>a3f65c2792add233ca8e5a3d3a76953db</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>IterQuantity *</type>
      <name>clone</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccessContiguous.html</anchorfile>
      <anchor>a795d41059acffbc5b16a227010e5d001</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>name</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccessContiguous.html</anchorfile>
      <anchor>af140e97df77466b25e994a3d8992656c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>has_storage_k</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccessContiguous.html</anchorfile>
      <anchor>aefe264c6116bf048ef3aba0f55c502d9</anchor>
      <arglist>(int offset) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>updated_k</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccessContiguous.html</anchorfile>
      <anchor>ac754016900f29c4cc58a5f4e6feb54f2</anchor>
      <arglist>(int offset) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>last_updated</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccessContiguous.html</anchorfile>
      <anchor>ae03bc391985c0650f0babccca58a46c0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_not_updated_k</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccessContiguous.html</anchorfile>
      <anchor>a6298ffe5daf2c837d70e32ab0ef63c16</anchor>
      <arglist>(int offset)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_all_not_updated</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccessContiguous.html</anchorfile>
      <anchor>a710504c6270eb33102b20fedd8bb5f28</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>will_loose_mem</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccessContiguous.html</anchorfile>
      <anchor>a974b35055405b400f9bb77abf732499b</anchor>
      <arglist>(int offset, int set_offset) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>next_iteration</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccessContiguous.html</anchorfile>
      <anchor>abd6fdce01482f2c030493b7dd5e6f9e5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_concrete_type</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccessContiguous.html</anchorfile>
      <anchor>a508bb13436f69be5987f7e4daca25c0b</anchor>
      <arglist>(std::ostream &amp;out) const </arglist>
    </member>
    <member kind="function">
      <type>T_info &amp;</type>
      <name>get_k</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccessContiguous.html</anchorfile>
      <anchor>aa79445587e8370a0d6c415ba21a2d026</anchor>
      <arglist>(int offset)</arglist>
    </member>
    <member kind="function">
      <type>const T_info &amp;</type>
      <name>get_k</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccessContiguous.html</anchorfile>
      <anchor>aa3f7421395e8458fe53ccd44bc52dfcc</anchor>
      <arglist>(int offset) const </arglist>
    </member>
    <member kind="function">
      <type>T_info &amp;</type>
      <name>set_k</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccessContiguous.html</anchorfile>
      <anchor>a83ff5510a11a64c9fcdcb9391291bcb4</anchor>
      <arglist>(int offset)</arglist>
    </member>
    <member kind="function">
      <type>T_info &amp;</type>
      <name>set_k</name>
      <anchorfile>classIterationPack_1_1IterQuantityAccessContiguous.html</anchorfile>
      <anchor>ac25736cd6fe826ef9d0e13738a4ba7ae</anchor>
      <arglist>(int set_offset, int get_offset)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~IterQuantity</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>a87a76d3556a8cbc5c03c4a12bef15d0a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assert_has_storage_k</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>a833fdbd2c8174ccc1fea37618593b1f8</anchor>
      <arglist>(int offset) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assert_updated_k</name>
      <anchorfile>classIterationPack_1_1IterQuantity.html</anchorfile>
      <anchor>ab3208fb4059c83847caa683c13a91735</anchor>
      <arglist>(int offset) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>IterationPack::InvalidTypeCastException</name>
    <filename>classIterationPack_1_1InvalidTypeCastException.html</filename>
  </compound>
  <compound kind="dir">
    <name>IterationPack</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/moocho/src/IterationPack/</path>
    <filename>dir_572ebd03d330e98a30a15c810b073f1f.html</filename>
    <dir>src</dir>
  </compound>
  <compound kind="dir">
    <name>src</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/moocho/src/IterationPack/src/</path>
    <filename>dir_cd92210d75cd5cb255f71fc7cf5a7772.html</filename>
    <file>IterationPack_Algorithm.cpp</file>
    <file>IterationPack_Algorithm.hpp</file>
    <file>IterationPack_AlgorithmSetOptions.cpp</file>
    <file>IterationPack_AlgorithmSetOptions.hpp</file>
    <file>IterationPack_AlgorithmState.cpp</file>
    <file>IterationPack_AlgorithmState.hpp</file>
    <file>IterationPack_AlgorithmStep.hpp</file>
    <file>IterationPack_AlgorithmTracker.cpp</file>
    <file>IterationPack_AlgorithmTracker.hpp</file>
    <file>IterationPack_AlgorithmTrackerComposite.cpp</file>
    <file>IterationPack_AlgorithmTrackerComposite.hpp</file>
    <file>IterationPack_cast_iq.cpp</file>
    <file>IterationPack_cast_iq.hpp</file>
    <file>IterationPack_CastIQMember.cpp</file>
    <file>IterationPack_CastIQMember.hpp</file>
    <file>IterationPack_IterQuantity.cpp</file>
    <file>IterationPack_IterQuantity.hpp</file>
    <file>IterationPack_IterQuantityAccess.hpp</file>
    <file>IterationPack_IterQuantityAccessContiguous.hpp</file>
    <file>IterationPack_IterQuantityAccessContiguousDecl.hpp</file>
    <file>IterationPack_IterQuantityAccessContiguousDef.hpp</file>
    <file>IterationPack_print_algorithm_step.cpp</file>
    <file>IterationPack_print_algorithm_step.hpp</file>
    <file>IterationPack_Types.hpp</file>
  </compound>
  <compound kind="dir">
    <name>src</name>
    <path>/Users/sscoll/Downloads/trilinos-11.0.3-Source/packages/moocho/src/</path>
    <filename>dir_68267d1309a1af8e8297ef4c3efbcdba.html</filename>
    <dir>IterationPack</dir>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>IterationPack: General Framework for Iterative Algorithms</title>
    <filename>index</filename>
  </compound>
</tagfile>

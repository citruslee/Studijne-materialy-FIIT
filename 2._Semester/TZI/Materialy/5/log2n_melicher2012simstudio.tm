<?xml version="1.0" encoding="UTF-8"?>
<turingmachine>
	<meta>
		<author />
		<title />
		<description />
		<created>23.11.2012 19:18:22</created>
		<modified>23.11.2012 22:15:53</modified>
	</meta>
	<machine type="TM">
		<tapes>
			<tape id="0">
				<head id="0" position="-4" />
				<cell position="-4">1</cell>
				<cell position="-3">1</cell>
				<cell position="-2">1</cell>
				<cell position="-1">1</cell>
				<cell position="0">1</cell>
				<cell position="1">1</cell>
				<cell position="2">1</cell>
				<cell position="3">1</cell>
				<cell position="4">$</cell>
			</tape>
		</tapes>
		<states>
			<state id="q0">
				<name>q0</name>
				<comment />
				<x>52</x>
				<y>323</y>
				<initial />
			</state>
			<state id="qf">
				<name>qf</name>
				<comment />
				<x>190</x>
				<y>40</y>
				<final />
			</state>
			<state id="q1">
				<name>q1</name>
				<comment />
				<x>185</x>
				<y>267</y>
			</state>
			<state id="q3">
				<name>q3</name>
				<comment />
				<x>466</x>
				<y>170</y>
			</state>
			<state id="q2">
				<name>q2</name>
				<comment />
				<x>312</x>
				<y>303</y>
			</state>
			<state id="q4">
				<name>q4</name>
				<comment />
				<x>610</x>
				<y>254</y>
			</state>
			<state id="q5">
				<name>q5</name>
				<comment />
				<x>730</x>
				<y>306</y>
			</state>
		</states>
		<transitions>
			<transition>
				<from>q0</from>
				<to>qf</to>
				<read>Blank</read>
				<write>Blank</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>q0</from>
				<to>qf</to>
				<read>$</read>
				<write>$</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>q0</from>
				<to>q0</to>
				<read>1_</read>
				<write>1_</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>q0</from>
				<to>q1</to>
				<read>1</read>
				<write>1_</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>q1</from>
				<to>qf</to>
				<read>$</read>
				<write>$</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>q1</from>
				<to>q1</to>
				<read>1_</read>
				<write>1_</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>q1</from>
				<to>q2</to>
				<read>1</read>
				<write>1</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>q2</from>
				<to>q4</to>
				<read>$</read>
				<write>$</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>q2</from>
				<to>q2</to>
				<read>1_</read>
				<write>1_</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>q2</from>
				<to>q3</to>
				<read>1</read>
				<write>1_</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>q3</from>
				<to>q4</to>
				<read>$</read>
				<write>$</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>q3</from>
				<to>q3</to>
				<read>1_</read>
				<write>1_</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>q3</from>
				<to>q2</to>
				<read>1</read>
				<write>1</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>q4</from>
				<to>q4</to>
				<read>1</read>
				<write>1</write>
				<move>Right</move>
				<comment />
			</transition>
			<transition>
				<from>q4</from>
				<to>q5</to>
				<read>Blank</read>
				<write>1</write>
				<move>Left</move>
				<comment />
			</transition>
			<transition>
				<from>q5</from>
				<to>q5</to>
				<read>1</read>
				<write>1</write>
				<move>Left</move>
				<comment />
			</transition>
			<transition>
				<from>q5</from>
				<to>q5</to>
				<read>1_</read>
				<write>1_</write>
				<move>Left</move>
				<comment />
			</transition>
			<transition>
				<from>q5</from>
				<to>q5</to>
				<read>$</read>
				<write>$</write>
				<move>Left</move>
				<comment />
			</transition>
			<transition>
				<from>q5</from>
				<to>q0</to>
				<read>Blank</read>
				<write>Blank</write>
				<move>Right</move>
				<comment />
			</transition>
		</transitions>
		<code>// prvu najdenu jednotku podciarknem
δ (q0,Blank) = (qf,Blank,R)
δ (q0,$) = (qf,$,R)
δ (q0,1_) = (q0,1_,R)
δ (q0,1) = (q1,1_,R)

// druhu jednotku iba preskocim
δ (q1,$) = (qf,$,R)
δ (q1,1_) = (q1,1_,R)
δ (q1,1) = (q2,1,R)

// uz mozme pripisat nakoniec 1
// v q2 iba osetrim zvysok vstupu
δ (q2,$) = (q4,$,R)
δ (q2,1_) = (q2,1_,R)
δ (q2,1) = (q3,1_,R)

δ (q3,$) = (q4,$,R)
δ (q3,1_) = (q3,1_,R)
δ (q3,1) = (q2,1,R)

// k vysledku pripisem 1
δ (q4,1) = (q4,1,R)
δ (q4,Blank) = (q5,1,L)

// presuniem sa na zaciatok
δ (q5,1) = (q5,1,L)
δ (q5,1_) = (q5,1_,L)
δ (q5,$) = (q5,$,L)
δ (q5,Blank) = (q0,Blank,R)
</code>
	</machine>
</turingmachine>
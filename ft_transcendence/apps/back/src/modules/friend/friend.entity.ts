import { Entity, PrimaryGeneratedColumn, Column, BaseEntity, CreateDateColumn, UpdateDateColumn, OneToMany, JoinTable } from "typeorm"
import User from "../user/user.entity"

@Entity("friend")
export default class Friend extends BaseEntity {
	@PrimaryGeneratedColumn()
    id: number;

	@Column()
	user_id: number;

	@Column()
	friend_id: number;

	@CreateDateColumn()
	created_at: Date;

	@UpdateDateColumn()
	updated_at: Date;
}
